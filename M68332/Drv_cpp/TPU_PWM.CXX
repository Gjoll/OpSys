//
//           File Name:  TPU_PWM.cxx
//          Class Name:  TPU_PWM
//		See the TPU_PWM.hxx file for details.
//
//  Author:  Mark Giebler
//
//  Revisions:
//

#include <TPU_PWM.hxx>

//-----------------------------------------------------------------------
//
//	Name:	TPU_PWM
//	Description:
//              constructor
//  PWM control.  Rates are given in nano seconds.  The resolution
//	is in steps of 1920 nano seconds.
//	This resolution can be changed if the low level
// 	init of the TPU registers is changed.  The TCR1 clock divisor would
// 	need to be changed and the base TPU class would need to change to
// 	initialize nanoSecondsTCR1 correctly.
//
//
//	Arguments:
//		(1) channel (r)		Specifies the TPU channel
//		(2) polority (r)	Specifies the output's polority
//		(3) period (r)		Specifies the period in nano seconds
//		(4) onTime (r)		Specifies the on time in nano seconds
//		(5) priority (r)	Specifies the priority of the TPU channel
//
//	Returns:
//		none
//
//	Author: Mark Giebler
//	Revisions:
//
TPU_PWM::TPU_PWM( BYTE channel, TPU_PWM_Polarity thePolarity,
                long initPeriod, long initOnTime,
                Priorities initPriority,
	            BOOL interruptEnable,
	            INTRPT_FUNC intFunc, short intLvl
                ) :
		        Tpu( PWM, channel,  interruptEnable,
	                    intFunc,  intLvl )
{
	INT16 channelControl;

	polarity = thePolarity;
	onTime = (INT16U) ((long)initOnTime / nanoSecondsTCR1);
	period = (INT16U) ((long)initPeriod / nanoSecondsTCR1);

	channelControl = TPU_PWM_CHANNEL_CONTROL | TPU_PWM_PSC_FPH;

	loadParameter( PARAM_ONE, channelControl );
	loadParameter( PARAM_THREE, (INT16) 0 );
	loadParameter( PARAM_FOUR, (INT16) 0 );
	loadHSRR( TPU_PWM_HSRR_INITIALIZE ); //initialize
	loadParameter( PARAM_FOUR, (INT16)period );
	loadParameter( PARAM_THREE, (INT16)onTime );
	loadCPR( initPriority );
}

//-----------------------------------------------------------------------
//
//	Name:	TPU_PWM
//	Description:
//		destructor
//
//	Arguments:
//		none
//
//	Returns:
//		none
//
//	Revisions:
//
TPU_PWM::~TPU_PWM()
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
//	Revisions:
//
void TPU_PWM::setPriority( Priorities thePriority )
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
void TPU_PWM::setDutyCycle( long newPeriod, long newOnTime )
{
	onTime = (INT16U) ((long)newOnTime / nanoSecondsTCR1);
	period = (INT16U) ((long)newPeriod / nanoSecondsTCR1);
	loadParameter( PARAM_FOUR, period );
	loadParameter( PARAM_THREE, onTime );
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
//	Revisions:
//
void TPU_PWM::start( void )
{
	loadParameter( PARAM_THREE, onTime );
	loadParameter( PARAM_FOUR, period );
	loadHSRR( TPU_PWM_HSRR_IMMEDIATE_UPDATE );
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
void TPU_PWM::start( long newPeriod, long newOnTime)
{
	onTime = (INT16U) ((long)newOnTime / nanoSecondsTCR1);
	period = (INT16U) ((long)newPeriod / nanoSecondsTCR1);
	loadParameter( PARAM_THREE, onTime );
	loadParameter( PARAM_FOUR, period );
	loadHSRR( TPU_PWM_HSRR_IMMEDIATE_UPDATE );
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
//	Revisions:
//
void TPU_PWM::stop( void )
{
	if(polarity == TPU_PWM_POLARITY_NORMAL)
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
	loadHSRR( TPU_PWM_HSRR_IMMEDIATE_UPDATE );
}
