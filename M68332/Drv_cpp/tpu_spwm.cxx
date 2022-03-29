//
//           File Name:  TPU_SPWM.cxx
//          Class Name:  TPU_SPWM
//		See the TPU_SPWM.hxx file for details.
//
//              Author:  Mark Giebler
//           Revisions:
//

#include <TPU_SPWM.hxx>

//-----------------------------------------------------------------------
//
//	Name:	TPU_SPWM
//	Description:
//              constructor
//  SPWM control.  Rates are given in nano seconds.  The resolution
//	is in steps of 1920 nano seconds.
//
//	Arguments:
//		(1) channel (r)		Specifies the TPU channel
//		(2) linkChannel		If mode 2 TPU then First channel to link to.
//							If mode 0 or 1 then this is the channel
//							of the TPU REF_ADDR1 and REF_ADDR2 will point to.
//		(3) linkCount		Number of channels in link block, (1 to 8) or
//							if a linked channel this is ignored.
//		(4) mode			Mode of operation (mode 0, 1, or 2)
//		(5) polority (r)	Specifies the output's polority
//		(6) period (r)		Specifies the period in nano seconds
//		(7) onTime (r)		Specifies the on time in nano seconds
//		(8) priority (o)	Specifies the priority of the TPU channel
//		(9) interruptEnable Specifies if interrupts are to be enabled at start up.
//		(10) IntFunc		Interrupt subroutine, only needed if interrupts are used.
//		(11) intLvl			Interrupt level used on the CPU. Only needed (or used)
//							on the first TPU instantiated...
//	Returns:
//		none
//
//	Author: Mark Giebler
//	Revisions:
//

TPU_SPWM::TPU_SPWM( BYTE channel, BYTE linkChannel, BYTE linkCount,
				TPU_SPWM_Mode  initMode,
				TPU_SPWM_Polarity thePolarity,
                long initPeriod, long initOnTime, long initDelay,
                Priorities initPriority,
	            BOOL interruptEnable,
	            INTRPT_FUNC intFunc, short intLvl
                ) :
		        Tpu( SPWM, channel,  interruptEnable,
	                    intFunc,  intLvl )
{
	INT16 channelControl,
			paramFive = 0;

	polarity = thePolarity;
	mode = initMode;

	onTime = (INT16U) ((long)initOnTime / nanoSecondsTCR1);
	period = (INT16U) ((long)initPeriod / nanoSecondsTCR1);
	delay =  (INT16) ((long)initDelay / nanoSecondsTCR1);

	channelControl = TPU_SPWM_CHANNEL_CONTROL | TPU_SPWM_PSC_FPH;
	loadParameter( PARAM_ONE, channelControl );
	loadParameter( PARAM_THREE, (INT16) 0 );
	loadParameter( PARAM_FOUR, (INT16) 0 );

	switch( mode ){
	case TPU_SPWM_MODE_2:
		// only mode 2 TPU modes can generate links...
		// setup TPU channel block  this TPU will link to,
		paramFive = (linkChannel << 12) | ( linkCount << 8 );
		//
		// drop into mode 0 to finish up...
		//
	case TPU_SPWM_MODE_0:
		// set REF_ADDR1 to point to LASTRISE of sync channel
		paramFive |= linkChannel << 4;
		loadParameter( PARAM_FOUR, (INT16)period );
		loadParameter( PARAM_THREE, (INT16)onTime );
    	loadParameter( PARAM_FIVE, paramFive );
		loadParameter( PARAM_SIX, (INT16) delay );
		break;
	case TPU_SPWM_MODE_1:
		// point REF_ADDR1 to linkChannels Nextrise.
		paramFive = ((linkChannel << 4)+2) << 8;
		// point REF_ADDR2 to linkChannels LASTRISE.
		paramFive += (linkChannel << 4);
		loadParameter( PARAM_FOUR, (INT16)delay );
		loadParameter( PARAM_THREE, (INT16)onTime );
    	loadParameter( PARAM_FIVE, paramFive );
		break;
    };
    //
    // setup this TPU to go...
    loadHSQR( mode );
	loadHSRR( TPU_SPWM_HSRR_INITIALIZE ); //initialize
	// remove parameter load from here....
	loadCPR( initPriority );
}

//-----------------------------------------------------------------------
//
//	Name:	TPU_SPWM
//	Description:
//		destructor
//
//	Arguments:
//		none
//
//	Returns:
//		none
//
//	Author: Mark Giebler
//	Revisions:
//
TPU_SPWM::~TPU_SPWM()
{
	loadCPR( TPU_OFF ); //stop the tpu
}

//-----------------------------------------------------------------------
//
//	Name:	setPriority
//	Description:
//		Set the TPU priority.
//
//	Arguments:
//		(1) priority (r)	Specifies the TPU priority.
//
//	Returns:
//		none
//
//	Author: Mark Giebler
//	Revisions:
//
void TPU_SPWM::setPriority( Priorities thePriority )
{
	loadCPR( thePriority );
}

//-----------------------------------------------------------------------
//
//	Name:	setDutyCycle
//	Description:
//		Set the output wave form's duty cycle at the next low-to-high transition.
//
//	Arguments:
//		(1) newPeriod (r)	Specifies the wave form's period in nSec.
//		(2) newOnTime (r)	Specifies the wave form's on time in nSec.
//
//	Returns:
//		none
//
//	Author: Mark Giebler
//	Revisions:
//
void TPU_SPWM::setDutyCycle( long newPeriod, long newOnTime, long newDelay )
{
	onTime = (INT16U) ((long)newOnTime / nanoSecondsTCR1);
	period = (INT16U) ((long)newPeriod / nanoSecondsTCR1);
	delay = (INT16) ((long)newDelay / nanoSecondsTCR1);

	switch( mode ){
	case TPU_SPWM_MODE_2:
	case TPU_SPWM_MODE_0:
		loadParameter( PARAM_FOUR, (INT16)period );
		loadParameter( PARAM_THREE, (INT16)onTime );
		loadParameter( PARAM_SIX, (INT16) delay );
		break;
	case TPU_SPWM_MODE_1:
		loadParameter( PARAM_FOUR, (INT16)delay );
		loadParameter( PARAM_THREE, (INT16)onTime );
		break;
    };

}

//-----------------------------------------------------------------------
//
//	Name:	start
//	Description:
//		Start TPU output immediately using the previously specified
//		period and on time.
//
//	Arguments:
//		none
//
//	Returns:
//		none
//
//	Author: Mark Giebler
//	Revisions:
//
void TPU_SPWM::start( void )
{
	loadParameter( PARAM_THREE, onTime );
	loadParameter( PARAM_FOUR, period );
	loadHSRR( TPU_SPWM_HSRR_IMMEDIATE_UPDATE );
}

//-----------------------------------------------------------------------
//
//	Name:	start
//	Description:
//		Start TPU output immediately with the specified period and on time.
//
//	Arguments:
//		(1) newPeriod (r)	Specifies the wave form's period in nSec .
//		(2) newOnTime (r)	Specifies the wave form's on time in nSec .
//
//	Returns:
//		none
//
//	Author: Mark Giebler
//	Revisions:
//
void TPU_SPWM::start( long newPeriod, long newOnTime)
{
	onTime = (INT16U) ((long)newOnTime / nanoSecondsTCR1);
	period = (INT16U) ((long)newPeriod / nanoSecondsTCR1);
	loadParameter( PARAM_THREE, onTime );
	loadParameter( PARAM_FOUR, period );
	loadHSRR( TPU_SPWM_HSRR_IMMEDIATE_UPDATE );
}

//-----------------------------------------------------------------------
//
//	Name:	stop
//	Description:
//		Stop the TPU's output immediately.
//
//	Arguments:
//		none
//
//	Returns:
//		none
//
//	Author: Mark Giebler
//	Revisions:
//
void TPU_SPWM::stop( void )
{
	if(polarity == TPU_SPWM_POLARITY_NORMAL)
	{
		//set the duty cycle to 0%
		loadParameter( PARAM_THREE, 0 );
		loadParameter( PARAM_FOUR, period );
	}
	else
	{
		//set the duty cycle to 100%
		loadParameter( PARAM_THREE, period );
		loadParameter( PARAM_FOUR, period );
	}
	loadHSRR( TPU_SPWM_HSRR_IMMEDIATE_UPDATE );
}
