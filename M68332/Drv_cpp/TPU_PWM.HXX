//
//           File Name:  TPU_PWM.hxx
//          Class Name:  TPU_PWM
//         Description:
//		Time Processor Unit - Pulse-Width Modulation.
//		(M68300 Family TPU Refenence Manual).
//
//		Methods:
//		TPU_PWM		The constructor.
//		setDutyCycle	Set or change the output duty cycle.
//		setPriority	Sets the tpu priority (TPU_LOW, TPU_MID, TPU_HIGH).
//		start		Starts tpu output.
//		stop		Stops tpu output.

//           Revisions:
//

#ifndef TPU_PWM_HXX
#define TPU_PWM_HXX

#include <Tpu.hxx>


//PWM output polority
enum TPU_PWM_Polarity{
	TPU_PWM_POLARITY_NORMAL, //low when output is stopped
	TPU_PWM_POLARITY_INVERTED //high when output is stopped
};

/*Priorities as defined in Tpu.hxx
enum Priorities {
    TPU_OFF = 0,
    TPU_LOW = 1,
    TPU_MID = 2,
    TPU_HIGH = 3
};*/

//PWM Channel_Control Options:
#define TPU_PWM_CHANNEL_CONTROL		0X90 /*TCR1*/
#define TPU_PWM_PSC_FPH			0X01 /*FORCE PIN HIGH*/
#define TPU_PWM_PSC_FPL			0X02 /*FORCE PIN LOW*/
#define TPU_PWM_PSC_NF			0X03 /*DO NOT FORCE*/

//HSRR parameter
#define TPU_PWM_HSRR_NO_REQUEST		0x0
#define TPU_PWM_HSRR_IMMEDIATE_UPDATE	0x1
#define TPU_PWM_HSRR_INITIALIZE		0x2
#define TPU_PWM_HSRR_UNDEFINED		0X3

//=======================================================
//pulse-width modulation tpu class
class TPU_PWM: public Tpu
{
public:
	//------------------------------------------------------------------
	//user methods
	void setDutyCycle( long period, long onTime ); //set or change the output duty cycle
	void setPriority( Priorities priority ); //set the tpu priority: TPU_LOW, TPU_MID, TPU_HIGH
	void start( void ); //start tpu output
	void start( long period, long onTime ); //start tpu output with the specified duty cycle
	void stop( void ); //stop tpu output

	//------------------------------------------------------------------
	//constructor
	TPU_PWM(BYTE channel, TPU_PWM_Polarity polarity = TPU_PWM_POLARITY_NORMAL,
		    long period = 100000, long onTime = 50000,
		    Priorities priority = TPU_MID,
	        BOOL interruptEnable = FALSE,
	        INTRPT_FUNC intFunc = 0, short intLvl = 6
		);

	~TPU_PWM();

private:
	INT16U	onTime,
		period,
		polarity;
};

#endif
