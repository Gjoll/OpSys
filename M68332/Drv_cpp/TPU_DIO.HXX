//
//           File Name:  TPU_DIO.hxx
//          Class Name:  TPU_DIO
//	Description:
//		Time Processor Unit - Direct Input Output.
//		(M68300 Family TPU Refenence Manual).
//
//	Public Methods:
//		setInterruptEdge
//			This method sets the edge (neither, either, rising, falling)
//			that will cause the TPU to interrupt.
//
//		setPriority
//			This method sets the TPU priority.
//
//		interruptAfterTransition
//			This method sets the TPU to interrupt  after a
//			specified transition.
//
//		interruptAfterRateMatch
//			This method sets the TPU to interrupt every time
//			a specified rate match occurs.
//
//		cont
//			This method causes the TPU to continue from where
//			it was stopped.
//
//		stop
//			This method stops the TPU from interrupting.
//
//      input
//          This method forces an update to the pinLevel register so
//          the current state of the pin can be read.  May cause an
//          interrupt to happen if interrupts are enabled for the TPU.
//
//      pinLevel
//          This method returns the latest value in pinLevel..This may
//          not be the current state of the pin..but it does not cause
//          an interrupt.
//
//              Author:  Mark Giebler
//           Revisions:
//

#ifndef TPU_DIO_HXX
#define TPU_DIO_HXX


#include <Tpu.hxx>
//#include <TPU_Chan.hxx> // tpu channels

//TPU_DIO_CHANNEL_CONTROL
#define	TPU_DIO_NO_EDGE_DECTECT		    0x03
#define	TPU_DIO_RISING_EDGE_DECTECT	    0x07
#define	TPU_DIO_FALLING_EDGE_DECTECT	0x0b
#define	TPU_DIO_EITHER_EDGE_DECTECT	    0x0f
#define TPU_DIO_PAC_NOCHANGE            0x13

#define TPU_DIO_TCR1_TCR1               0x03
#define TPU_DIO_TCR1_TCR2               0x23
#define TPU_DIO_TCR2_TCR1               0x43
#define TPU_DIO_TCR2_TCR2               0x63
#define TPU_DIO_TBS_NOCHANGE            0x100



//TPU_DIO_ host sequence bits
#define	TPU_DIO_TRAN		0x0
#define	TPU_DIO_MATCH		0x1
#define TPU_DIO_RECORD      0x2 // input when HSR 11

//HSRR parameter
#define TPU_DIO_HSRR_NO_REQUEST		0x0
#define TPU_DIO_HSRR_OUTPUT_H		0x1
#define TPU_DIO_HSRR_OUTPUT_L		0x2
#define TPU_DIO_HSRR_INITIALIZE     0x3

// define modes:
#define TPU_DIO_TRANSITION 0
#define TPU_DIO_RATE    1
#define TPU_DIO_OUTPUT  2
#define TPU_DIO_INPUT   3


//=======================================================
class TPU_DIO: public Tpu
{
public:
	//---------------------------------------------------------------------
	//user methods
	void setInterruptEdge(INT16U interruptEdge); //set interrupt edge:
	void setPriority(Priorities newPriority); //set the tpu priority
	void interruptAfterTransition( INT16U edge = 0 );
	void interruptAfterRateMatch( INT16U rate = 0 );

	void output(INT16U io); // force pin to state.
	INT16U input(); //input pin state
	void cont(void); //continue using previous settings
	void stop(void); //stop
	INT16U pinLevel( void );

	//---------------------------------------------------------------------
	//constructor/destructor
	// constructor for transition mode matching...interrupts enabled
	TPU_DIO( BYTE channel,
	        INT16U interruptEdge, /* TPU_DIO_RISING_EDGE_DECTECT */
			Priorities initialPriority, /* TPU_MID */
	        BOOL interruptEnable = FALSE,
	        INTRPT_FUNC intFunc = 0, short intLvl = 6
			 );
	// constructor for discrete output control, interrupts off
	TPU_DIO( BYTE channel, INT16U initVal );
	// constructor for discrete input, interrupts off
	TPU_DIO( BYTE channel );
	// constructor for rate matching, interrupts enabled...
	TPU_DIO(BYTE channel, INT16U matchRate, INT16U matchMode, /* TPU_DIO_TCR1_TCR1*/
	        Priorities initialPriority, /* TPU_MID */
	        BOOL interruptEnable = FALSE,
	        INTRPT_FUNC intFunc = 0, short intLvl = 6
			 );
	~TPU_DIO();

private:
	Priorities priority;
	INT16U type;
};

#endif
