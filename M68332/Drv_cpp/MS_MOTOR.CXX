///////////////////////////////////////////////////////////////////////////
//
// File: ms_motor.cxx
// Class: MicroStep_Motor
//
//
// Author: Mark Giebler
//
//
///////////////////////////////////////////////////////////////////////////
#include <ms_motor.hxx>
#include <scan.hxx>
//
// define zero current value for motor windings.
//
#define A_0_CURRENT 127
#define B_0_CURRENT 127

//  ***********************
// external TPU objects.
//  ***********************
extern TPU_SPWM sampleHoldTPU;
extern TPU_SPWM motorTPU;
// ##############################################################
//		static objects
// ##############################################################
//
// initialize the static interrupt vector table offset to 0.
// This will be set to the real value when the first motor object
// is instantiated.
//
VECTOR MicroStep_Motor::IntVector = (VECTOR) 0;

// ########################################################
//
// The next global variables are
// used by interrupt subroutine that drives the motors.
// Pointer to these variables need to be passed to the
// constructors for the X motor and Y motor.
//
// ########################################################
//
// pointers to the table of motor value pairs to send to the motors.
unsigned char *Y_motor_table, *X_motor_table;
//
// Pointers to the current profiles being run...
Profile *Y_profile, *X_profile;
//
// index into waveTable
// define as union between a long and two shorts.
// This will provide for fixed point addition of fractional steps...
index Y_index, X_index;
//
// absolute location counter
// multiplied by 256.
unsigned long Y_absolute = 0, X_absolute = 0;

short lastADC;

// ##############################################################
//
// Interrupt Function: MS_MotorHandler
// Description:
//  interrupt handler for the X and Y micro stepped motors.
//  Writes 4 values out to the DAC. One value for each of the 4
//  motor phases.  (2 Phases per motor).
//
// Author: Mark Giebler
//
// ##############################################################
extern "C" void interrupt MS_MotorHandler( void )
{
    register unsigned char value;
    register short y_index;
    register short x_index;
    //
    // get index values in to registers
    // Total is a fixed point number.  Upper 8 bits are whole part,
    // lower 8 bits are fractional part.
    // Whole part is the current step to uses from the wave table.
    // Multiply whole part by 2 since table has two entries per step.
    // NOTE rounding up since bit 7 of fractional part becomes bit 1 of
    // whole part.
    y_index = Y_index.total >> 7;
    x_index = X_index.total >> 7;
    //
    // get the value for phase A of motor X
    value = X_motor_table[x_index];
    // write that to DAC
    *((unsigned char *)(X_MOTOR_DAC_A)) = value;
    //
    // do the same for phase B
    // get the value for phase A of motor X
    value = X_motor_table[x_index+1];
    // write that to DAC
    *((unsigned char *)(X_MOTOR_DAC_B)) = value;
    //
    // get the value for phase A of motor Y
    value = Y_motor_table[y_index];
    // write that to DAC
    *((unsigned char *)(Y_MOTOR_DAC_A)) = value;
    //
    // do the same for phase B
    // get the value for phase A of motor Y
    value = Y_motor_table[y_index+1];
    // write that to DAC
    *((unsigned char *)(Y_MOTOR_DAC_B)) = value;
    //
    // now write to transfer loaded DAC value to the DAC outputs
    // simultaneously. (value is just used as a dummy)
    *((unsigned char *)(LOAD_DACS)) = value;
    //
    // update index by adding the amount of the next step.
    // reload the registers...
    x_index = X_index.total;
    y_index = Y_index.total;
    //
    // now add the next part of the step...and absolute location
    x_index += X_profile->direction;
    X_absolute += X_profile->direction;
    y_index += Y_profile->direction;
    Y_absolute += Y_profile->direction;
    //
    // table is fixed at 128 steps.  So do and to make wrap around to
    // start of table
    x_index &= 0x7fff;
    y_index &= 0x7fff;
    //
    // update index variables in memory
    Y_index.total = y_index;
    X_index.total = x_index;
	//
	// determine if finished with curent profile
    //
    if( X_profile->moveDistance-- == 0 )
    	X_profile = X_profile->next;
    if( Y_profile->moveDistance-- == 0 )
    	Y_profile = Y_profile->next;
//
// read ADC here.  It is OK to read last since the TPU is used
// to gate the sample and hold before the interrupt is generated.
// The sample is held at the value sampled just before the interrupt.
//
	lastADC = *((short*)(LASER_ADC)) & ADC_MASK;
    //
    //
    // service the interrupt bit
    motorTPU.resetInterruptStatus();

    //
    // previous interrupt level gets enable from RTE instruction
    // when we leave this function....
}

//
// declare small table with 0 current value for both motor windings..
//
static unsigned char stoppedTable[4] = { A_0_CURRENT, B_0_CURRENT, 0, 0 };

static Profile stoppedProfile = { 1, 0,  &stoppedProfile };
static Profile homeProfile = { 1, +256,  &homeProfile };
///////////////////////////////////////////////////
//
// Constructor
// Description:
//	Initialize internals.  Set state of motor to MOTOR_STOPPED.
//  The motor windings are set to a zero current value.
//  (User must call goHome() to fully initialize motor object so that
//  the absolute location of the scan head can be determeined...)
//  The first motor object that calls the constructor also causes
//  the interrupt handler to be placed in the 68332's interrupt vector
//  table...
//
// Inputs:
//  homeDirection   This just sets the polarity of the direction the motor
//                  must turn to move to the home sensor. There are 2
//                  sensors, either can be the home.
//  handlerTable    a handle to a pointer to the table the interrupt
//                  subroutine will run through to move the motor.
//                  This will be one of 2 values for the scanner project:
//                  &X_motor_table or &Y_motor_table.
//
// handlerTblIndex a pointer to the interrupt handler's index variable
//                  for the motor: &X_index or &Y_index.
// handlerAbsolute	a pointer to the absolute location of the motor in
//					microsteps * 256.
// handlerProfile	a handle to the interrupts profile pointer.
//					This will be X_profile or Y_profile for the scanner.
//
// stepRate			This is the step rate when the motor is running
//					in microstepping mode, units are nanoSeconds.
//
//  wavTbl  	OPTIONAL.  Defaults to the table "waves".
//				It is a pointer to an array of waveTable structures.
//				These structures contain the wave form shapes availble to drive
//          	the motor with.  See mot_tbl.hxx for format...

MicroStep_Motor::MicroStep_Motor(
                                    int homeDirection, // 1 or -1
                                    unsigned char ** handlerTable,
                                    index * handlerTblIndex,
                                    unsigned long * handlerAbsolute,
                                    Profile ** handlerProfile,
                                    unsigned long stepRate,
                                    TableStruct *wavTbl) :

	                                MotorState( MOTOR_UNINITIALIZED ),
                                    waveTables( wavTbl ),
                                    homeRotationDir( homeDirection ),
                                    StepRate( stepRate )
{
    // set handle to interrupt handler's pointer to the
    // pattern of bytes to be sent to motors
    waveTables = wavTbl;
	AbsoluteLoc = handlerAbsolute;
	activeWaveTable = handlerTable;
	*activeWaveTable = stoppedTable; // initialize to 0 current position
	activeIndex = handlerTblIndex;
	activeIndex->total = 0;

	activeProfile = handlerProfile;
	*activeProfile = &stoppedProfile;


	activeLastStepIndex = 0;// position in wave table of last step in above
	activeWave = MODIFIED_SINE_1;  // wave form table used to generate above sequence

	nextWaveTable = 0;
	nextIndex.total = 0;
	nextLastStepIndex = 0;
	nextProfile = 0;
	nextWave = MODIFIED_SINE_1;

	MaxSteps = 		0x7fffffff;
	*AbsoluteLoc = 	0x7fffffff;	/* absolute micro steps from home */

//
// install the interrupt handler..
// We install it into a trap vector so that we can call the interrupt
// routine from within the program in addition to being called by an
// external interrupt.
//
    if( IntVector == 0 )
        IntVector = interrupt_68k.setTrapHandler( MS_MotorHandler );
	//
	// set motor DAC values to 0 current values
	//
	MotorState = disable();
	//
	// Set the step rate of the motor interrupt and the
	// sample and hold window.
	//
	setStepRate( StepRate, StepRate/2L, StepRate/4L, StepRate/8L );
}
MicroStep_Motor::~MicroStep_Motor()
{
	disable();
}
// **************************************************************
// createProfile
//
// Creates a profile for moving the motor the requested distance.
//	Distance is relative from what ever the currnet position is
//  at the time the profile is executed.
//
// Input:
//	microSteps	positive or negative number of microsteps to move.
//	ratePercent	the percentage rate of the speed to move.  100 is 100%
//
// Returns:
//	a pointer to the created profile.  Tha last profile should be linked
//	to a profile that has 0 as the distance to move and it's next pointer
//	should point to itself.
//	If 0 is returned then profile could not be created.
//
Profile * MicroStep_Motor::createProfile( long microSteps, short ratePercent )
{
	Profile* newProfile = 0;

	return newProfile;
}

//
// absoluteLoc
//
// Return the location of the motor in micro steps.
//
unsigned long MicroStep_Motor::absoluteLoc( )
{
	return (*AbsoluteLoc >> 8);
}
// #############################################################
//
// Method: setStepRate
// Description:
//	Changes the step rate of the TPU's used to control the motor
// 	interrupt rate and the laser pulse and sample rates.
//
// Input:  All  units are nanoSeconds.
//	newStepRate	the new motor step rate to set,
//	laserOnTime	 The time to leave the laser on for.  Must be less
//				than newStepRate by at least 2000 nSec.  Suggested
//				time about 1/2 to 3/4 of newStepRate.
//	sampleTime	The length of time to sample the laser detector.
//				NOTE: this time must be less than 1/2 the newRate.
//				Typically it should be 1/4 to 1/8 of newStepRate.
//  laserOffDelay  This is the amount of time to wait after the
//				sample of the laser detector to turn off the laser driver.
//				This should be at least 4000 nSec but less than 1/4
//				of newRate.
//
void MicroStep_Motor::setStepRate( 	long newRate,
									long laserOnTime,
									long sampleTime,
									long laserOffDelay )
{
	sampleHoldTPU.setDutyCycle( newRate, sampleTime, 2000);
	motorTPU.setDutyCycle( newRate, newRate - laserOnTime,
								sampleTime + laserOffDelay );
}


// ##############################################################
//
// Method: goHome
// Description:
//  Sets a profile to quickly move the motor to the home position.
//  It starts the motor running and waits for the motor state to
//  be MOTOR_STOPPED_AT_HOME.
//  The limit switch interrupt handler will cause this to be set.
//
int MicroStep_Motor::goHome()
{
	int status = MOTOR_OK;
	// WAVE saveWave;

	homeProfile.moveDistance = homeRotationDir * 0x0ffffffe;
	homeProfile.direction = 256 * homeRotationDir;
	homeProfile.next = &homeProfile; // make it loop on this profile
									// when limit switch is hit,
									// motor will be stopped.
	//
	// stop the motor where it is at and hold it there.
	hold();
	nextWave = activeWave;
	//
	// setup wave table for profile
	sequenceProfile( &homeProfile );
	//
	// execute the nextProfile...
	executeProfile(  );
	//
	// need to wait for limit switch hit...or status change to MOTOR_STOPPED
    //while ( ((volatile) MotorState) != MOTOR_STOPPED)
        ;
    *AbsoluteLoc = 0; // we are home...
    //waveMode( saveWave );  // restore original wave mode.

    return status;
}
// ##############################################################
// Method: hold
// Description:
//  This will hold the motor at the current position.
//  This is done by making a 1 pair table that has
//  the values that were last driven to the motor windings.
//  The interrupt handler will just keep sending this pair
//  to the motors.
//  This release the memory used for the previously active table.
//
// ##############################################################

void MicroStep_Motor::hold()
{
//
// disable interrupts ...
//
	motorTPU.maskInterrupt();
    interrupt_68k.disableInterrupts( );

    activeIndex->total -= 256;  // point to the last value sent to motor.
    if ( activeIndex->total < 128)
        activeIndex->total += 256;
    //
    // put those values in the stop table so motor can be held
    // at its current position.
    stoppedTable[0] = *activeWaveTable[activeIndex->total >> 7];
    stoppedTable[1] = *activeWaveTable[(activeIndex->total >> 7)+1];
    //
    // delete the previous profile if needed.
    if ( *activeProfile != &stoppedProfile &&
    	 *activeProfile != &homeProfile )
    	delete [] *activeProfile;
    *activeWaveTable = stoppedTable;
    activeIndex->total = 0;
//
// enable interrupts.
	motorTPU.unmaskInterrupt();
    interrupt_68k.enableInterrupts(  );

}
// *********************************************************
//
// disable
//
//  stops motor movement immediately.  And sets motor windings
//  to 0 current value.
//
int MicroStep_Motor::disable()
{
	int status = MOTOR_DISABLED;
//
// disable ALL interrupts ...
//
	motorTPU.maskInterrupt();

    interrupt_68k.disableInterrupts( );
    //
    // delete table if allocated from memory
    if ( *activeProfile != &stoppedProfile &&
    	 *activeProfile != &homeProfile )
    	delete [] *activeProfile;
    *activeProfile = &stoppedProfile;
	activeIndex->total = 0;
    //
    // since motor interrupts are not enabled.
    // single step through the zero current table just set...

    singleStep();
	state( MOTOR_STOPPED );

//
// enable interrupts to previous level.
	motorTPU.unmaskInterrupt();
    interrupt_68k.enableInterrupts(  );

    return status;
}
// ************************************************************
//
// enable
//
// allows motor movement to be requested by setting status to OK.
// Also enables the motor TPU interrupts to run.
//
int MicroStep_Motor::enable()
{
	int status = MOTOR_OK;
//
// enable interrupts from the motor TPU
//
	motorTPU.enableInterrupt();

    return status;
}
// ***************************************************************
// waveMode
//
//	Used to set a new wave type used in microstepping the motor.
//
//	returns the previous wave type.
//
WAVE MicroStep_Motor::waveMode( WAVE waveMd )
{
	WAVE orig  = activeWave;
	activeWave = waveMd;
    return orig;
}
// ################################################################
//
// Method: sequenceProfile
// Description:
//  Used to create the sequence wave table for the motor.
//  builds the sequence using the wave table specified by nextWave.
//  Builds starting from activeLastStep index into current wave table.
//
// Returns:
//  MOTOR_OK if sequence built OK.
//  error code otherwise ( BAD_WAVE | NO_MEMEORY )
// Updates:
//	nextMoveSequnce	points to new sequnce in memory.
//	nextSeqLen		length of new sequence
// ################################################################

int MicroStep_Motor::sequenceProfile( Profile* profile )
{
	int status = MOTOR_OK;
	int index;
    int seqIndex = 0;
	int stepRate, distance = 0, steps = 0, stepSum = 0;
	int tableSize;
	long totalSteps = 0;
	unsigned char *waveTable;

	if( nextProfile != 0 ) // previous sequence not executed yet
	    delete( nextProfile ) ;

    nextProfile = profile;
    if ( setWaveform( nextWave ) == BAD_WAVE )
        return BAD_WAVE;

    //
    // set the last index used.
    //
    nextLastStepIndex = index;
	nextIndex.total = 0; // must scale activeLastStepIndex based on stepRate

    return status;
}
// ***********************************************************
// setWaveform
//
// Used to set a new waveform at the motor.  updates
// the interrupt routines motor pointer right away.
//
// Input:
//	waveform	which waveform to use.
//
// Returns: BAD_WAVE if requested wave is not one of the tables available
//			MOTOR_OK if waveform was set.
//
int MicroStep_Motor::setWaveform( WAVE waveform )
{
    //
    // get motor wave shape table to use
    //
    int i = 0;
    while ( waveTables[ i ].waveType != WAVE_END &&
            waveTables[ i ].waveType != waveform )
            i++;
    //
    //  check for table not found...
    if ( waveTables[i].waveType == WAVE_END )
        return BAD_WAVE;

    *activeWaveTable = waveTables[i].waveTable;
	return MOTOR_OK;
}
// ##########################################################
//
// Method: executeProfile
// Description:
//  Starts execution of the next profile.
//
int MicroStep_Motor::executeProfile( )
{
	int status;
	//
	// turn off all interrupts.
	//
	motorTPU.maskInterrupt();
    interrupt_68k.disableInterrupts( );

	//
	// install new sequence into interrupt variable set
	//

	if( *activeWaveTable != nextWaveTable ){
	    *activeWaveTable = nextWaveTable;
	    activeIndex->total = nextIndex.total;
    }
    // delete the previous profile if needed.
    if ( *activeProfile != &stoppedProfile &&
    	 *activeProfile != &homeProfile )
    	delete [] *activeProfile;

    *activeProfile = nextProfile;
	activeLastStepIndex = nextLastStepIndex;

	nextProfile = 0;
	nextWaveTable = 0;
	nextLastStepIndex = 0;
	//
	// enable interrupts
	motorTPU.unmaskInterrupt();
    interrupt_68k.enableInterrupts(  );
	//
	// make sure TPU interrupts are enabled...
	status = enable();

    return status;
}
//
// Method: singleStep
// Description:
//  Moves the motor one step in the currently active sequence.
//  Calls the interrupt handler directly to do this...
//
// BUG: this should be a trap instruction...
//
int MicroStep_Motor::singleStep()
{
//
// call interrupt handler using trap instruction
//    MS_MotorHandler( );
    interrupt_68k.trap( IntVector );
    return MOTOR_OK;
}
//
// returns the current motor state.
int MicroStep_Motor::state()
{
	return MotorState;
}
//
// Method: motorAtHome
// Description:
//  Called when the motor home limit switch triggers.
//  This will stop the motor and set the state to MOTOR_STOPPED_AT_HOME.
//
int MicroStep_Motor::atHomeLimit()
{

    hold();
    return state( MOTOR_STOPPED_AT_HOME );
}
//
// Method: motorAtFar
// Description:
//  Called when the motor far limit switch triggers.
//  This will stop the motor and set the state to MOTOR_STOPPED_FAR_LIMIT.
//
int MicroStep_Motor::atFarLimit()
{

    hold();
    return state( MOTOR_STOPPED_FAR_LIMIT );
}
// ################################################################
//
// private:
//
// ################################################################
//
// Method: absoluteLoc( long )
// Description:
//  Used to set the absolute location
//
unsigned long MicroStep_Motor::absoluteLoc(  unsigned long absLoc )
{
	*AbsoluteLoc = absLoc << 8;
    return absLoc;
}
//
// Method: motorState( int )
// Description:
//  Used to set the motor state.
int MicroStep_Motor::state( int newState )
{
	MotorState = newState;
	return MotorState;
}
