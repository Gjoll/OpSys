//
//           File Name:  TPU_ITC.cxx
//          Class Name:  TPU_ITC
//	Description:
//		See the TPU_ITC.hxx file for details.
//
//

#include <TPU_ITC.hxx>

//-----------------------------------------------------------------------
//
//	Name:	TPU_ITC
//	Description:
//              constructor
//
//	Arguments:
//		(1) channel (r)		Specifies the TPU channel
//		(2) initialPriority (r)	Specifies the priority of the TPU channel
//					Valid values are: TPU_LOW, TPU_MID, TPU_HIGH,
//					TPU_OFF.
//		(3) interruptEdge (r)	Specifies the interrupt edge.
//					Valid values are:
//					NO_EDGE_DECTECT, RISING_EDGE_DECTECT,
//					FALLING_EDGE_DECTECT, EITHER_EDGE_DECTECT.
//
//	Returns:
//		none
//
//
TPU_ITC::TPU_ITC(BYTE channel,
                INT16U interruptEdge,
                Priorities initialPriority,
	            BOOL interruptEnable,
	            INTRPT_FUNC intFunc, short intLvl
                ) :
		        Tpu( DIO, channel,  interruptEnable,
	                    intFunc,  intLvl )
{
	setInterruptEdge( interruptEdge ); //set edge dectect
	loadParameter( PARAM_TWO, (INT16U)TPU_ITC_P2 ); //set required things
	priority = initialPriority;
}

//-----------------------------------------------------------------------
//
//	Name:	TPU_ITC
//	Description:
//		destructor.  Turns off TPU before destruction...
//
//	Arguments:
//		none
//
//	Returns:
//		none
//
//
TPU_ITC::~TPU_ITC()
{
	maskInterrupt();
	loadCPR( TPU_OFF ); //stop the tpu
}

//-----------------------------------------------------------------------
//
//	Name:	setInterruptEdge
//	Description:
//		Sets the edge (neither, either, rising, falling)
//		that will cause the TPU to interrupt.
//
//	Arguments:
//		(1) interruptEdge (r)	Specifies the edge that will cause an interrupt.
//					Valid values are:
//					NO_EDGE_DECTECT, RISING_EDGE_DECTECT,
//					FALLING_EDGE_DECTECT, EITHER_EDGE_DECTECT.
//
//	Returns:
//		none
//
//
void TPU_ITC::setInterruptEdge( INT16U interruptEdge )
{
	loadParameter( PARAM_ONE, interruptEdge );

}

//-----------------------------------------------------------------------
//
//	Name:	setPriority
//	Description:
//		Sets the TPU priority.
//
//	Arguments:
//		(1) newPriority (r)	Specifies the TPU priority. Valid
//					values are: TPU_LOW, TPU_MID, TPU_HIGH,
//					TPU_OFF.
//
//	Returns:
//		none
//
//
void TPU_ITC::setPriority( Priorities newPriority )
{
	priority = newPriority;
}

//-----------------------------------------------------------------------
//
//	Name:	interruptAfterXCounts
//	Description:
//		This method sets the TPU to interrupt once after a
//		specified number of counts.
//
//	Arguments:
//		(1) counts (r)		Specifies the number of counts.
//
//	Returns:
//		none
//
//
void TPU_ITC::interruptAfterXCounts(INT16U counts)
{
	resetInterruptStatus();		// reset any pending interrupt
	loadParameter(PARAM_THREE, counts); //set the number of counts until interrupt
	loadHSQR((INT16)TPU_ITC_ONE_SHOT); //set one shot
	loadHSRR((INT16)TPU_ITC_HSRR_INITIALIZE); //initialize
	loadCPR(priority); //start the tpu
    enableInterrupt();  // enable this TPU's interrupt bit.
}

//-----------------------------------------------------------------------
//
//	Name:	interruptEveryXCounts
//	Description:
//		This method sets the TPU to interrupt every time
//		a specified number of counts is counted.
//
//	Arguments:
//		(1) counts (r)		Specifies the number of counts.
//
//	Returns:
//		none
//
//
void TPU_ITC::interruptEveryXCounts( INT16U counts )
{
	resetInterruptStatus();		// reset any pending interrupt
	loadParameter( PARAM_THREE, counts ) ; //load number of counts until interrupt
	loadHSQR( (INT16)TPU_ITC_CONTINUOUS ); //load duty cycle
	loadHSRR( (INT16)TPU_ITC_HSRR_INITIALIZE ); //initialize
	loadCPR( priority ); //start the tpu
    enableInterrupt();  // enable this TPU's interrupt bit.
}

//-----------------------------------------------------------------------
//
//	Name:	cont
//	Description:
//		This method causes the TPU to continue from where
//		it was stopped.
//
//	Arguments:
//		none
//
//	Returns:
//		none
//
//
void TPU_ITC::cont(void)
{
	loadHSRR( (INT16)TPU_ITC_HSRR_INITIALIZE ); //initialize
	loadCPR( priority ); //start the tpu
	unmaskInterrupt();
}

//-----------------------------------------------------------------------
//
//	Name:	stop
//	Description:
//		This method stops the TPU from interrupting.
//
//	Arguments:
//		none
//
//	Returns:
//		none
//
//
void TPU_ITC::stop(void)
{
	loadCPR( TPU_OFF ); //stop the tpu
}

//-----------------------------------------------------------------------
//
//	Name:	readCurrentCount
//	Description:
//		Reads the current count from the TPU's TRANS_COUNT register.
//
//	Arguments:
//		none
//
//	Returns:
//		The current count.
//
//
INT16U TPU_ITC::readCurrentCount(void)
{
	return( readParameter(PARAM_FOUR) );
}
