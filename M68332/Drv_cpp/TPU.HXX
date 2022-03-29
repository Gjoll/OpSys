//
//           File Name: Tpu.hxx
//          Class Name: Tpu
//         Description:
// Tpu provides an object to be used to access a single TPU channel.
// TPU channels range from 0 - 15.  They are mapped to specific
// functionality by the hardware as follows:
//
//     Channel #             Hardware Signal
//        0                     PARRALEL PORT STROBE
//        1                     LIMIT SWITCH 1
//        2                     LIMIT SWITCH 2
//        3                     LIMIT SWITCH 3
//        4                     LIMIT SWITCH 4
//        5                     SAMPLE/HOLD GATE
//        6                     LASER DRIVER
//        7                     SAMPLE HOLD INPUT
//        8                     Auto feed from parallel port
//        9                     Select in from parallel port
//        10                    Init in from parallel port
//        11                    UNUSED
//        12                    UNUSED
//        13                    UNUSED
//        14                    UNUSED
//        15                    UNUSED
//
// Refer to the "M68300 Family TPU Reference Manual" for details on the
// TPU and its functions.
//
// Tpu contains the following public methods:
//
//    loadHSQR                      - load the channel's host sequence reg
//    loadHSRR                      - load the channel's host svc request reg
//    loadCPR                       - load the channel's priority reg
//    loadParameter                 - load the channel's parameter RAM
//    readParameter                 - read the channel's parameter RAM
//    ppwaReadLW                    - read the channel's lower word (period/
//                                  -   pulse width), ppwa function
//                                  -   only
//    ppwaReadUB                    - read the channel's overflow, ppwa
//                                      function only
//    Tpu                           - constructor
//    ~Tpu                          - destructor
//
//  Mark Giebler
//
//  Revisions:
//

#ifndef TPU_HXX
#define TPU_HXX

// Include files.
#include <ioaddr.hxx>
#include <int_68k.h>
// Defines.
#define CISR_CHNL0 0x0001
#define CISR_CHNL1 0x0002
#define CISR_CHNL2 0x0004
#define CISR_CHNL3 0x0008
#define CISR_CHNL4 0x0010
#define CISR_CHNL5 0x0020
#define CISR_CHNL6 0x0040
#define CISR_CHNL7 0x0080
#define CISR_CHNL8 0x0100
#define CISR_CHNL9 0x0200
#define CISR_CHNL10 0x0400
#define CISR_CHNL11 0x0800
#define CISR_CHNL12 0x1000
#define CISR_CHNL13 0x2000
#define CISR_CHNL14 0x4000
#define CISR_CHNL15 0x8000
//
// TCR1 prescale values, section 2.1.1 in TPU manual.
//
#define _2_uSec (0)
#define _4_uSec (0x2000)
#define _8_uSec (0x4000)
#define _16_uSec (0x6000)

#define TCR2_DIV8	(0x0200) /* TCR2 pin gate DIV8 clock */
// Externals.

// Types.
// FunctionTypes are all of the TPU functions available.
// Refer to the "M68300 Family TPU Reference Manual" for details on the
// functions.  Section numbers are given after each type...
enum FunctionTypes {
    SPWM =   0x7, // 3.5 Sync PWM
    DIO =    0x8, // 3.1 Discrete I/O
    PWM =    0x9, // 3.4 Pulse Width Modulation
    ITC =    0xA, // 3.2 Input Transition Counter
    PMAPMM = 0xB, // 3.6 Period Measurment
    PSP =    0xC, // 3.8 Position Sync'ed Pulse Gen
    SM =     0xD, // 3.9 Stepper Motor
    OC =     0xE, // 3.3 Output Compare
    PPWA =   0xF  // 3.10 Period/Pulse Width Accumulator
};

// ParamPositions is a type that defines the valid parameter
// positions within TPU parameter RAM.  For each channel, the
// TPU provides 7 parameters to be filled in according to
// which TPU function is to be executed.
// NOTE: this was copied from someone else.
//  They started with parameter 1 instead of 0 like all the
//  motorola documentation is.
enum ParamPositions {
    PARAM_ONE = 0,
    PARAM_TWO = 2,
    PARAM_THREE = 4,
    PARAM_FOUR = 6,
    PARAM_FIVE = 8,
    PARAM_SIX = 0xA,
    PARAM_SEVEN = 0xC
};

// Priorities are the valid priorities at which a channel
// can be set to run.
enum Priorities {
    TPU_OFF = 0,
    TPU_LOW = 1,
    TPU_MID = 2,
    TPU_HIGH = 3
};

// Class definition.
class Tpu {
public:
    void loadHSQR(INT16 hsqrValue);
    void loadHSRR(INT16 hsrrValue);
    void loadCPR(Priorities cprValue);
    void loadParameter(ParamPositions paramNumber,
		       INT16 paramValue );
    INT16U readParameter(ParamPositions paramNumber);

    BYTE ppwaReadUB();
    INT16U ppwaReadLW();

    void unmaskInterrupt(){
        if (interruptsEnabled)
            *((INT16U*)(CIER)) |= (chnlIntMask);};
    void maskInterrupt(){
            *((INT16U*)(CIER)) &= (~chnlIntMask);};

    void enableInterrupt(){
            interruptsEnabled = TRUE;
            *((INT16U*)(CIER)) |= (chnlIntMask);};
    void disableInterrupt(){
            interruptsEnabled = FALSE;
            *((INT16U*)(CIER)) &= (~chnlIntMask);};

	unsigned short getInterruptStatus() {
		// returns zero if no new interrupt pending,
		// otherwise returns non zero.
		return ((*((unsigned short*)(CISR))) & chnlIntMask);
	};
    void resetInterruptStatus() {
    	  // must read first
        unsigned short currentISR = *((unsigned short*)(CISR));
          // then clear the bit to reset interrupt pending state.
        *((unsigned short*)(CISR)) = (~chnlIntMask) & currentISR;
    };
    Tpu(FunctionTypes tpuFunction,
	    BYTE channel,
	    BOOL interruptEnable = FALSE,
	    INTRPT_FUNC intFunc = 0, short intLvl = 6);
    ~Tpu();

protected:
    static long nanoSecondsTCR1;	// nanoSecond rate of TCR1, used by PWM

private:
    Interrupt_68K* intObj;
    INT32 hsqr;        // address of host sequence register
    INT32 hsrr;        // address of host service request register
    INT32 cpr;         // address of channel priority register
    INT16 chnlMask;    // mask for hsqr, hsrr, cpr for this channel
    INT16 chnlShift;   // # of bits to shift for hsqr, hsrr, and cpr
		                //  for this channel
    INT32 paramStart;  // address of paramater RAM for this channel
//    static VECTOR baseVector;   // base interrupt vector for TPU
    INT16 chnlIntMask;          // channel interrupt mask bit
    BOOL interruptsEnabled;
    void setSampleRate();	//  determines the TCR1 rate.

};

#endif
