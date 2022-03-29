//
//           File Name:  TPU_ITC.hxx
//          Class Name:  TPU_ITC
//	Description:
//		Time Processor Unit - Input Transition Counter.
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
//		interruptAfterXCounts
//			This method sets the TPU to interrupt once after a
//			specified number of counts.
//
//		interruptEveryXCounts
//			This method sets the TPU to interrupt every time
//			a specified number of counts is counted.
//
//		cont
//			This method causes the TPU to continue from where
//			it was stopped.
//
//		stop
//			This method stops the TPU from interrupting.
//
//		readCurrentCount
//			This method returns the current count from
//			the TPU's TRANS_COUNT register.
//
//

#ifndef TPU_ITC_HXX
#define TPU_ITC_HXX


#include <Tpu.hxx>
//#include <TPU_Chan.hxx> //tpu channels

//TPU_ITC_PARAMETER2 no links and bank address not used
#define	TPU_ITC_P2	0x01c /* 0x0e */

//TPU_ITC_CHANNEL_CONTROL
#define	TPU_ITC_NO_EDGE_DECTECT		    0x03
#define	TPU_ITC_RISING_EDGE_DECTECT	    0x07
#define	TPU_ITC_FALLING_EDGE_DECTECT	0x0b
#define	TPU_ITC_EITHER_EDGE_DECTECT	    0x0f

//TPU_ITC_DUTYCYCLE
#define	TPU_ITC_ONE_SHOT		0x0
#define	TPU_ITC_CONTINUOUS		0x1

//HSRR parameter
#define TPU_ITC_HSRR_NO_REQUEST		0x0
#define TPU_ITC_HSRR_INITIALIZE		0x1

//=======================================================
class TPU_ITC: public Tpu
{
public:
	//---------------------------------------------------------------------
	//user methods
	void setInterruptEdge(INT16U interruptEdge); //set interrupt edge:
	void setPriority(Priorities newPriority); //set the tpu priority
	void interruptAfterXCounts(INT16U interruptCounts); //interrupt once after x counts
	void interruptEveryXCounts(INT16U interruptCounts); //interrupt after every x counts
	void cont(void); //continue using previous settings
	void stop(void); //stop
	INT16U readCurrentCount(void);

	//---------------------------------------------------------------------
	//constructor/destructor
	TPU_ITC(BYTE channel, INT16U interruptEdge = TPU_ITC_RISING_EDGE_DECTECT,
			 Priorities initialPriority = TPU_MID,
	            BOOL interruptEnable = FALSE,
	            INTRPT_FUNC intFunc = 0, short intLvl = 6
			 );
	~TPU_ITC();

private:
	Priorities priority;
};

#endif
