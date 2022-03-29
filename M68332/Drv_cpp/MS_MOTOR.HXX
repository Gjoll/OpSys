//////////////////////////////////////////////////////////////////////////
//
//   File: ms_motor.hxx
//  Description:
//		This file is the declaration of the MicroStep_Motor class.
//		MicroStep_Motor class is the micro stepping motor class.
//		It contains methods to control a micro stepped motor.
//		It generates the DAC tables needed to generate the
//		wave forms to micro step the motor.
//
//
// Author: Mark J Giebler
//
//////////////////////////////////////////////////////////////////////////
#ifndef MS_MOTOR_HXX
#define MS_MOTOR_HXX
#include <mot_tbl.hxx> // wave table
#include <int_68k.h>
#include <ioaddr.hxx> // address defines for chip selects
#include <tpu_spwm.hxx>
//
// define the motor addresses
//
#define X_MOTOR_DAC_A	(DAC_A)
#define X_MOTOR_DAC_B 	(DAC_B)
#define Y_MOTOR_DAC_A	(DAC_C)
#define Y_MOTOR_DAC_B	(DAC_D)
//
// Profile structure used to define motor movement profile.
// moveDistance
//	is the number of unique valued steps to make.  This value
//	is decremented by the interrupt routine, when zero, the
//	next profile is used.
// direction
//	+2, 0, or -2, added to the index into the wavetable.  0 will
//	cause the motor to hold its last position.  + rotates CW, - rotate CCW.
// stepRate
//	Percentage of "normal" table used.  256 == 100%.  This is also
//	The length of the waveTable.  All profiles in a linked list have
//	the same table.   When 256 (100%), one cycle,  (angular
// 	distance to rotate.)  is
// 	128 steps = 1.8 degrees of motor shaft movement.
// next
//	pointer to the next profile, can point to itself or an earlier
//	profile to make the motor run forever.  To cause the motor to
//	stop, the last profile
//	must have "direction" set to 0 and moveDistance greater than 0
//	and next pointing to itself.  This will hold the motor at the last step.
//
typedef struct Profile{
	long	moveDistance;	// interrupt cycles to run this profile...
	int		direction;		// +, 0 or - direction to move index each
							// interrupt.  +256
							// moves one full motor step. less than 256 adds
							// a fraction of movement.
	Profile* next;
} Profile;
//
// general return status from method calls.
#define MOTOR_OK	0
#define BAD_WAVE -1
#define MOTOR_TOO_FAR -2	/* motor too far from home */
#define MOTOR_DISABLED -3  	/* motor not able to run until enableMotor() */
#define HOME_TIMEOUT -4 	/* timeout when seeking home */
#define END_OF_PROFILE -5   /* motor completed profile */
#define NO_MEMORY   -20     /* new failed to return needed resource */

//
// define rotation polarity
#define CW (1)
#define CCW (-1)
//
// define motor states
#define MOTOR_UNINITIALIZED -1 /* absolute motor position unknown */
#define MOTOR_STOPPED 0
#define MOTOR_STOPPED_AT_HOME 1
#define MOTOR_STOPPED_FAR_LIMIT 2
#define MOTOR_RUNNING 5
//
// define micro seconds multiplier
#define MICROsec (1000L)
//
// define stuff for motor interrupt handler.
//
// The handler needed by the motorTPU.
extern "C" void interrupt MS_MotorHandler( void );
//
// global var's needed by motor constructors
//
// pointers to the table of motor value pairs to send to the motors.
extern unsigned char *Y_motor_table, *X_motor_table;
//
// define union for integer and fractional parts of index
//
union index {
	unsigned short	total;
	struct {
	unsigned char 	fraction:8;
	unsigned char 	integer:8;
	} part;
};

extern index Y_index, X_index;
extern Profile *Y_profile, *X_profile;
extern unsigned long Y_absolute, X_absolute;

//
// Class: MicroStep_Motor
//
// This is the definition for the miro stepping motor class.
//	It provides control of a micro stepped stepping motor.
//
class MicroStep_Motor {
friend void interrupt MS_MotorHandler( void );
public:
	MicroStep_Motor( int homeDirection,
	                unsigned char ** handlerTable,
	                index *,
	                unsigned long *,
	                Profile **,
	                unsigned long stepRate,
	                TableStruct* wavTbl = waves);
	~MicroStep_Motor();
	unsigned long absoluteLoc();
    int goHome();
	int disable();	// stops motor movement NOW.
	int enable();  // allows motor movement to be requested.
	WAVE waveMode( WAVE waveMd );
	int sequenceProfile( Profile* profile );
	int executeProfile(  );
	int singleStep();
    int state();
    void hold();
    int atHomeLimit();
    int atFarLimit();
    void setStepRate( 	long newRate,
    					long laserOnTime,
						long sampleTime,
						long laserOffDelay );
    VECTOR getIntVector() { return IntVector; };
	int setWaveform( WAVE );		// sets the waveform used to drive the motor
	Profile * createProfile( long microSteps, short ratePercent );
//
// private methods
//
private:
    static VECTOR IntVector;    // vector where the interrupt handler is at in
                                // the 68332's interrupt table.
	TableStruct *waveTables;
	int homeRotationDir; 		// CW or CCW  (1 or -1)

	WAVE activeWave;
	unsigned char **activeWaveTable; // handle to interrupt handlers
	                                 // pointer to the wave table
    Profile **activeProfile;  // pointer to interrupt handler's Profile
                                	// pointer.
    index * activeIndex;       // pointer to the interrupt handler's variable
                             // used to index into the activeWaveTable.

	short activeLastStepIndex;    // index into wave table for last seq. step.

	WAVE nextWave;
	unsigned char *nextWaveTable;
	Profile* nextProfile;		// pointer to profile used to make next.
	index  nextIndex;
	short nextLastStepIndex;      // index into wave table for last seq. step.

	unsigned long * AbsoluteLoc;// absolute micro steps * 256 from home
	unsigned long MaxSteps;		// maximum steps from home.
	unsigned long StepRate;		// micro step rate of motor in nanoSeconds
	int MotorState;
	unsigned long absoluteLoc( unsigned long absLoc );

    int state( int newState );

};
#endif
