//
//           File Name:  TPU_DIO.cxx
//          Class Name:  TPU_DIO
//	Description:
//		See the TPU_DIO.hxx file for details.
//
//  Author:  Mark Giebler
//  Revisions:
//

#include <TPU_DIO.hxx>

//-----------------------------------------------------------------------
//
//	Name:	TPU_DIO
//	Description:
//      constructor for edge transition detection,
//      interrupts enabled
//
//	Arguments:
//		(1) channel (r)		Specifies the TPU channel
//		(2) interruptEdge (r)	Specifies the interrupt edge.
//					Valid values are:
//					NO_EDGE_DECTECT, RISING_EDGE_DECTECT,
//					FALLING_EDGE_DECTECT, EITHER_EDGE_DECTECT.
//		(3) initialPriority (r)	Specifies the priority of the TPU channel
//					Valid values are: TPU_LOW, TPU_MID, TPU_HIGH,
//					TPU_OFF.
//		(4) interruptEnable  Specifies if interrupts are to be enable in
//					the contructor.
//		(5) intFunc	Pointer to an interrupt function to handle interrupts
//					generatoed by this TPU channel.
//		(6) intLvl	The interrupt level to use for TPU interrupts. Only
//					The first object instantiated sets this. All TPU
//					channels must be at the same level.
//	Returns:
//		none
//
//	Author: Mark Giebler
//	Revisions:
//
TPU_DIO::TPU_DIO(BYTE channel, INT16U interruptEdge,
                Priorities initialPriority,
	            BOOL interruptEnable,
	            INTRPT_FUNC intFunc, short intLvl
                ) :
		        Tpu( DIO, channel,  interruptEnable,
	                    intFunc,  intLvl )
{
	setInterruptEdge( interruptEdge ); //set edge dectect
	priority = initialPriority;
	type = TPU_DIO_TRANSITION;
}
// constructor for discrete output control, no interrupts
TPU_DIO::TPU_DIO( BYTE channel, INT16U initVal ) :
		        Tpu( DIO, channel, FALSE )
{
        type = TPU_DIO_OUTPUT;
        output( initVal );
}
// constructor for discrete input
TPU_DIO::TPU_DIO( BYTE channel ) :
		        Tpu( DIO, channel, FALSE )
{
    type = TPU_DIO_INPUT;
	loadParameter( PARAM_ONE, 0x000f ); // detect either edge
	loadParameter( PARAM_THREE, 2 );	// match rate.
	loadHSQR( (INT16)TPU_DIO_TRAN ); //set the transition mode
	loadHSRR( (INT16)TPU_DIO_HSRR_INITIALIZE ); //initialize

}
// constructor for rate matching, interrupts enabled
TPU_DIO::TPU_DIO( BYTE channel, INT16U matchRate,
                INT16U matchMode /* TPU_DIO_TCR1_TCR1*/,
	            Priorities initialPriority, /* TPU_MID */
	            BOOL interruptEnable,
	            INTRPT_FUNC intFunc, short intLvl
                ) :
		        Tpu( DIO, channel,  interruptEnable,
	                    intFunc,  intLvl )
{
	loadParameter( PARAM_ONE, matchMode );
    loadParameter( PARAM_THREE, matchRate );
	priority = initialPriority;
    type = TPU_DIO_RATE;
}

//-----------------------------------------------------------------------
//
//	Name:	TPU_DIO
//	Description:
//		destructor.  Turns off TPU before destruction...
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
TPU_DIO::~TPU_DIO()
{
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
//					NO_EDGE_DECTECT,
//					RISING_EDGE_DECTECT,
//					FALLING_EDGE_DECTECT,
//					EITHER_EDGE_DECTECT.
//
//	Returns:
//		none
//
//	Author: Mark Giebler
//	Revisions:
//
void TPU_DIO::setInterruptEdge( INT16U interruptEdge )
{
	loadParameter( PARAM_ONE, interruptEdge );

}

//-----------------------------------------------------------------------
//
//	Name:	setPriority
//	Description:
//		Sets the TPU priority.  TPU not updated until stop()
//      followed by cont() calls are made...
//
//	Arguments:
//		(1) newPriority (r)	Specifies the TPU priority. Valid
//					values are: TPU_LOW, TPU_MID, TPU_HIGH,
//					TPU_OFF.
//
//	Returns:
//		none
//
//	Author: Mark Giebler
//	Revisions:
//
void TPU_DIO::setPriority(Priorities newPriority)
{
	priority = newPriority;
}
//---------------------------------------------------------------------
//
// Name: output
// Used to force the TPU pin to the requested state
//
//
//	Returns:
//		none
//
//	Author: Mark Giebler
//	Revisions:
//
void TPU_DIO::output(INT16U io)
{
    if (io == 0 )
	    loadHSRR((INT16)TPU_DIO_HSRR_OUTPUT_L); // 0
    else
	    loadHSRR((INT16)TPU_DIO_HSRR_OUTPUT_H); // 1

}


//-----------------------------------------------------------------------
//
//	Name:	interruptAfterTransition
//	Description:
//		This method sets the TPU to interrupt after a
//		specified edge occurs.
//
//	Arguments:
//		(1) edge (o)		Specifies the edge to interrupt on
//                          if zero then the edge specified in
//                          the constructor applies..
//
//	Returns:
//		none
//
//	Author: Mark Giebler
//	Revisions:
//
void TPU_DIO::interruptAfterTransition( INT16U edge )
{
	resetInterruptStatus();	// clear any previous interrupts
    if( edge != 0 )
	    loadParameter( PARAM_ONE, edge );
	loadParameter( PARAM_THREE, 2 );	// match rate.
	loadHSQR( (INT16)TPU_DIO_TRAN ); //set the transition mode
	loadHSRR( (INT16)TPU_DIO_HSRR_INITIALIZE ); //initialize
	loadCPR( priority ); //start the tpu
	resetInterruptStatus();	// clear any previous interrupts
							// added to try and get rid of bogus interrupt
    enableInterrupt();  // enable this TPU's interrupt bit.

}
//-----------------------------------------------------------------------
//
//	Name:	interruptAfterRateMatch
//	Description:
//		This method sets the TPU to interrupt  after a
//		specified rate is matched.
//
//	Arguments:
//		(1) rate (o)		Specifies the  match rate to interrupt on
//                          if zero then the rate specified in
//                          the constructor applies..
//
//	Returns:
//		none
//
//	Author: Mark Giebler
//	Revisions:
//
void TPU_DIO::interruptAfterRateMatch(INT16U rate)
{
	resetInterruptStatus();	// clear any previous interrupts
    if( rate != 0 )
	    loadParameter( PARAM_THREE, rate );
	loadHSQR( (INT16)TPU_DIO_RATE ); //set the transition mode
	loadHSRR( (INT16)TPU_DIO_HSRR_INITIALIZE ); //initialize
	loadCPR( priority ); //start the tpu
	resetInterruptStatus();	// clear any previous interrupts
							// added to try and get rid of bogus interrupt
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
//	Author: Mark Giebler
//	Revisions:
//
void TPU_DIO::cont(void)
{
	loadHSRR( (INT16)TPU_DIO_HSRR_INITIALIZE ); //initialize
	loadCPR( priority ); //start the tpu
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
//	Author: Mark Giebler
//	Revisions:
//
void TPU_DIO::stop(void)
{
	loadCPR( TPU_OFF ); //stop the tpu
}

//-----------------------------------------------------------------------
//
//	Name:	input
//	Description:
//		Reads the current TPU pin state.
//      If interrupts where enabled, this will generate an interrupt.
//	Arguments:
//		none
//
//	Returns:
//		0 or 1 depending on pin state..
//
//	Author: Mark Giebler
//	Revisions:
//
INT16U TPU_DIO::input(void)
{
    // force an update of the pin level register...
	loadHSQR( (INT16)TPU_DIO_RECORD );
	loadHSRR( (INT16)TPU_DIO_HSRR_INITIALIZE ); //initialize

	return( ((readParameter(PARAM_TWO) & 0x8000) ? 1 : 0) );
}
//
// Name: pinLevel
// Description:
//  Returns the latest value recorded in the pinLevel register.
//  Does not generate an interrupt, May not be the latest state
//  of the input pin.  But will be the last state of the pin that
//  caused an interrupt.
//
//	Arguments:
//		none
//
//	Returns:
//		0 or 1 depending on pin state..
//
//	Author: Mark Giebler
//	Revisions:
//
INT16U TPU_DIO::pinLevel(void)
{
	return( ((readParameter( PARAM_TWO ) & 0x8000) ? 1 : 0) );
}
