//
//           File Name:  TPU_SPWM.hxx
//          Class Name:  TPU_SPWM
//         Description:
//		Time Processor Unit - Pulse-Width Modulation.
//		(M68300 Family TPU Refenence Manual).
//
//		Methods:
//		TPU_SPWM		The constructor.
//		setDutyCycle	Set or change the output duty cycle.
//		setPriority	Sets the tpu priority (TPU_LOW, TPU_MID, TPU_HIGH).
//		start		Starts tpu output.
//		stop		Stops tpu output.

//              Author:  Mark Giebler
//           Revisions:
//

#ifndef TPU_SPWM_HXX
#define TPU_SPWM_HXX

#include <Tpu.hxx>


//SPWM output polority
enum TPU_SPWM_Polarity{
	TPU_SPWM_POLARITY_NORMAL, //low when output is stopped
	TPU_SPWM_POLARITY_INVERTED //high when output is stopped
};
enum TPU_SPWM_Mode{
		TPU_SPWM_MODE_0,
		TPU_SPWM_MODE_1,
		TPU_SPWM_MODE_2
};

//SPWM Channel_Control Options:
#define TPU_SPWM_CHANNEL_CONTROL		0X90 /*TCR1*/
#define TPU_SPWM_PSC_FPH			0X01 /*FORCE PIN HIGH*/
#define TPU_SPWM_PSC_FPL			0X02 /*FORCE PIN LOW*/
#define TPU_SPWM_PSC_NF			0X03 /*DO NOT FORCE*/

//HSRR parameter
#define TPU_SPWM_HSRR_NO_REQUEST		0x0
#define TPU_SPWM_HSRR_IMMEDIATE_UPDATE	0x1
#define TPU_SPWM_HSRR_INITIALIZE		0x2
#define TPU_SPWM_HSRR_UNDEFINED		0X3

//=======================================================
//pulse-width modulation tpu class
class TPU_SPWM: public Tpu
{
public:
	//------------------------------------------------------------------
	//user methods
	void setDutyCycle( long period, long onTime, long delay ); //set or change the output duty cycle
	void setPriority( Priorities priority ); //set the tpu priority: TPU_LOW, TPU_MID, TPU_HIGH
	void start( void ); //start tpu output
	void start( long period, long onTime ); //start tpu output with the specified duty cycle
	void stop( void ); //stop tpu output

	//------------------------------------------------------------------
	//constructor
	TPU_SPWM(BYTE channel, BYTE linkChannel, BYTE linkcount,
			TPU_SPWM_Mode mode,
			TPU_SPWM_Polarity polarity = TPU_SPWM_POLARITY_NORMAL,
		    long period = 200000, long onTime = 50000, long delay = 0,
		    Priorities priority = TPU_MID,
	        BOOL interruptEnable = FALSE,
	        INTRPT_FUNC intFunc = 0, short intLvl = 6
		);

	~TPU_SPWM();

private:
	INT16U	onTime,
		period,
		polarity;
	INT16 delay;
	TPU_SPWM_Mode mode;
};

#endif
