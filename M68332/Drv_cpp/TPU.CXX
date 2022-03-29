//
//           File Name: Tpu.cxx
//          Class Name: Tpu
//         Description:
// Tpu provides an object to be used to access a single TPU channel.
// TPU channels range from 0 - 15.  They are mapped to specific
// functionality by the hardware as follows:
//
//     Channel #             Hardware Signal
//        0                     Parallel Port Strobe Input
//        1                     Limit Switch 1
//        2                     Limit Switch 2
//        3                     Limit Switch 3
//        4                     Limit Switch 4
//        5                     Sample Hold Pulse (output)
//        6                     Laser Driver Pulse Output
//        7                     Sample Hold Pulse Input.
//        8                     UNUSED
//        9                     UNUSED
//        10                    UNUSED
//        11                    UNUSED
//        12                    UNUSED
//        13                    UNUSED
//        14                    UNUSED
//        15                    UNUSED
//
// Note that the parameter RAM and the TPU registers MUST be loaded
// as 16 bit values.  Loading byte values will cause the other byte
// of a 16 bit word to be loaded with all ones.
// Refer to the "M68300 Family TPU Reference Manual" for details on the
// TPU and its functions.
//
//  Mark Giebler
//
// Revisions:
//

// Include files.***************************************************
#include <tpu.hxx>

// Defines.*********************************************************
// The channel mask defines are used as masks to access
// 2 bits within a 16 bit register according to which
// channel is begin accessed.  They are used to modify HSQR, HSRR and
// CPR.
#define CHNL_MASK1 0xC000
#define CHNL_MASK2 0x3000
#define CHNL_MASK3 0x0C00
#define CHNL_MASK4 0x0300
#define CHNL_MASK5 0x00C0
#define CHNL_MASK6 0x0030
#define CHNL_MASK7 0x000C
#define CHNL_MASK8 0x0003

// The function mask defines are used as masks to access
// 4 bits within a 16 bit register according to which
// channel is begin accessed.  It is used to store
// the channel's function code which is an input parameter.
#define FN_MASK1 0x0FFF
#define FN_MASK2 0xF0FF
#define FN_MASK3 0xFF0F
#define FN_MASK4 0xFFF0

//
// define TPU interrupt arbitration
//
#define TPU_IARB (0x0d)

// Externals.*******************************************************

// Private methods.*************************************************


// Public methods.**************************************************
//
// Name: Tpu
//
// Description:
// TPU class for A mask of 68332.
// Tpu does the following:
//   1 - initializes the specified channel with the function
//   2 - sets the interrupt enable value
//   3 - sets up the TPU register addresses that pertain to
//       the given channel
//   4 - sets up the parameter addresses that pertain to the
//       given channel
//
// Arguments:
//   None
//
// Returns:
//   None
//
//
// Revisions:
//
//VECTOR Tpu::baseVector = (VECTOR) 0; // init static variable
VECTOR baseVector = (VECTOR) 0;   // base interrupt vector for TPU
long Tpu::nanoSecondsTCR1 = 0;	// nanoSeconds period of TCR1 clock

Tpu::Tpu(FunctionTypes tpuFunction,
	 BYTE channel,
	 BOOL interruptEnable, INTRPT_FUNC intFunc,
	 short intLvl ):
	 interruptsEnabled( interruptEnable )
{
    INT16 bits;

// 1 - get the right bit for this channel
    bits = 1;
    bits = ( bits << channel );
    chnlIntMask = bits;

// 2 - sets the interrupt enable value

    if ( baseVector == 0 ){
    	// if this is the first TPU object, init the common TPU registers.
    	//
        // configure TMCR  see section 2.1.1 in TPU manual
        *((INT16*)(TMCR)) = (INT16) (_2_uSec + TCR2_DIV8 + TPU_IARB);
		// set the rate of TCR1 based on the CPU clock speed.
        setSampleRate();
        // turn off all interrupts from TPU...
        *((INT16*)(CIER)) = 0;
        // reserve 16 contiguous vectors, one for each channel
        baseVector = interrupt_68k.reserve( 16 );
        // setup TICR register
        *((INT16*)(TICR)) = (INT16)((intLvl << 8) | baseVector);
        // init all TPU channels to inactive
        *((INT16*)(CPR0)) = 0;
        *((INT16*)(CPR1)) = 0;
    	// clear any pending interrupts that might be left over after restart
        *((INT16*)(CISR)) &= 0;
    }
    if( intFunc != 0  )
    // install interrupt handler for this tpu...
        interrupt_68k.setHandler( intFunc, baseVector + (VECTOR) channel );


// 3 - sets up the TPU register addresses that pertain to
//     the given channel
// 4 - sets up the parameter addresses that pertain to the
//     given channel
    switch (channel) {
	case 0:
	    *((INT16*)(CFSR3)) &=  FN_MASK4; // clear out chnl 0
	    *((INT16*)(CFSR3)) |=  tpuFunction; // 1
	    hsqr = (INT32)HSQR1;  // 3
	    hsrr = (INT32)HSRR1;  // 3
	    cpr = (INT32)CPR1;  // 3
	    chnlMask = CHNL_MASK8;  // 3
	    chnlShift = 0;  // 3
            paramStart = (INT32)CHNL0_PARAM_ADR;  // 4
	    break;
	case 1:
	    *((INT16*)(CFSR3)) &=  FN_MASK3; // clear out chnl 1
	    *((INT16*)(CFSR3)) |=  (tpuFunction << 4); // 1
	    hsqr = (INT32)HSQR1;  // 3
	    hsrr = (INT32)HSRR1;  // 3
	    cpr = (INT32)CPR1;  // 3
	    chnlMask = CHNL_MASK7;  // 3
	    chnlShift = 2;  // 3
            paramStart = (INT32)CHNL1_PARAM_ADR;  // 4
	    break;
	case 2:
	    *((INT16*)(CFSR3)) &=  FN_MASK2; // clear out chnl 2
	    *((INT16*)(CFSR3)) |=  (tpuFunction << 8); // 1
	    hsqr = (INT32)HSQR1;  // 3
	    hsrr = (INT32)HSRR1;  // 3
	    cpr = (INT32)CPR1;  // 3
	    chnlMask = CHNL_MASK6;  // 3
	    chnlShift = 4;  // 3
            paramStart = (INT32)CHNL2_PARAM_ADR;  // 4
	    break;
	case 3:
	    *((INT16*)(CFSR3)) &=  FN_MASK1; // clear out chnl 3
	    *((INT16*)(CFSR3)) |=  (tpuFunction << 12); // 1
	    hsqr = (INT32)HSQR1;  // 3
	    hsrr = (INT32)HSRR1;  // 3
	    cpr = (INT32)CPR1;  // 3
	    chnlMask = CHNL_MASK5;  // 3
	    chnlShift = 6;  // 3
            paramStart = (INT32)CHNL3_PARAM_ADR;  // 4
	    break;
	case 4:
	    *((INT16*)(CFSR2)) &=  FN_MASK4; // clear out chnl 4
	    *((INT16*)(CFSR2)) |=  tpuFunction; // 1
	    hsqr = (INT32)HSQR1;  // 3
	    hsrr = (INT32)HSRR1;  // 3
	    cpr = (INT32)CPR1;  // 3
	    chnlMask = CHNL_MASK4;  // 3
	    chnlShift = 8;  // 3
            paramStart = (INT32)CHNL4_PARAM_ADR;  // 4
	    break;
	case 5:
	    *((INT16*)(CFSR2)) &=  FN_MASK3; // clear out chnl 5
	    *((INT16*)(CFSR2)) |=  (tpuFunction << 4); // 1
	    hsqr = (INT32)HSQR1;  // 3
	    hsrr = (INT32)HSRR1;  // 3
	    cpr = (INT32)CPR1;  // 3
	    chnlShift = 10;  // 3
	    chnlMask = CHNL_MASK3;  // 3
            paramStart = (INT32)CHNL5_PARAM_ADR;  // 4
	    break;
	case 6:
	    *((INT16*)(CFSR2)) &=  FN_MASK2; // clear out chnl 6
	    *((INT16*)(CFSR2)) |=  (tpuFunction << 8); // 1
	    hsqr = (INT32)HSQR1;  // 3
	    hsrr = (INT32)HSRR1;  // 3
	    cpr = (INT32)CPR1;  // 3
	    chnlShift = 12;  // 3
	    chnlMask = CHNL_MASK2;  // 3
            paramStart = (INT32)CHNL6_PARAM_ADR;  // 4
	    break;
	case 7:
	    *((INT16*)(CFSR2)) &=  FN_MASK1; // clear out chnl 7
	    *((INT16*)(CFSR2)) |=  (tpuFunction << 12); // 1
	    hsqr = (INT32)HSQR1;  // 3
	    hsrr = (INT32)HSRR1;  // 3
	    cpr = (INT32)CPR1;  // 3
	    chnlMask = CHNL_MASK1;  // 3
	    chnlShift = 14;  // 3
            paramStart = (INT32)CHNL7_PARAM_ADR;  // 4
	    break;
	case 8:
	    *((INT16*)(CFSR1)) &=  FN_MASK4; // clear out chnl 8
	    *((INT16*)(CFSR1)) |=  tpuFunction; // 1
	    hsqr = (INT32)HSQR0;  // 3
	    hsrr = (INT32)HSRR0;  // 3
	    cpr = (INT32)CPR0;  // 3
	    chnlMask = CHNL_MASK8;  // 3
	    chnlShift = 0;  // 3
            paramStart = (INT32)CHNL8_PARAM_ADR;  // 4
	    break;
	case 9:
	    *((INT16*)(CFSR1)) &=  FN_MASK3; // clear out chnl 9
	    *((INT16*)(CFSR1)) |=  (tpuFunction << 4); // 1
	    hsqr = (INT32)HSQR0;  // 3
	    hsrr = (INT32)HSRR0;  // 3
	    cpr = (INT32)CPR0;  // 3
	    chnlMask = CHNL_MASK7;  // 3
	    chnlShift = 2;  // 3
            paramStart = (INT32)CHNL9_PARAM_ADR;  // 4
	    break;
	case 10:
	    *((INT16*)(CFSR1)) &=  FN_MASK2; // clear out chnl 10
	    *((INT16*)(CFSR1)) |=  (tpuFunction << 8); // 1
	    hsqr = (INT32)HSQR0;  // 3
	    hsrr = (INT32)HSRR0;  // 3
	    cpr = (INT32)CPR0;  // 3
	    chnlMask = CHNL_MASK6;  // 3
	    chnlShift = 4;  // 3
            paramStart = (INT32)CHNL10_PARAM_ADR;  // 4
	    break;
	case 11:
	    *((INT16*)(CFSR1)) &=  FN_MASK1; // clear out chnl 11
	    *((INT16*)(CFSR1)) |=  (tpuFunction << 12); // 1
	    hsqr = (INT32)HSQR0;  // 3
	    hsrr = (INT32)HSRR0;  // 3
	    cpr = (INT32)CPR0;  // 3
	    chnlMask = CHNL_MASK5;  // 3
	    chnlShift = 6;  // 3
            paramStart = (INT32)CHNL11_PARAM_ADR;  // 4
	    break;
	case 12:
	    *((INT16*)(CFSR0)) &=  FN_MASK4; // clear out chnl 12
	    *((INT16*)(CFSR0)) |=  tpuFunction; // 1
	    hsqr = (INT32)HSQR0;  // 3
	    hsrr = (INT32)HSRR0;  // 3
	    cpr = (INT32)CPR0;  // 3
	    chnlMask = CHNL_MASK4;  // 3
	    chnlShift = 8;  // 3
            paramStart = (INT32)CHNL12_PARAM_ADR;  // 4
	    break;
	case 13:
	    *((INT16*)(CFSR0)) &=  FN_MASK3; // clear out chnl 13
	    *((INT16*)(CFSR0)) |=  (tpuFunction << 4); // 1
	    hsqr = (INT32)HSQR0;  // 3
	    hsrr = (INT32)HSRR0;  // 3
	    cpr = (INT32)CPR0;  // 3
	    chnlMask = CHNL_MASK3;  // 3
	    chnlShift = 10;  // 3
            paramStart = (INT32)CHNL13_PARAM_ADR;  // 4
	    break;
	case 14:
	    *((INT16*)(CFSR0)) &=  FN_MASK2; // clear out chnl 14
	    *((INT16*)(CFSR0)) |=  (tpuFunction << 8); // 1
	    hsqr = (INT32)HSQR0;  // 3
	    hsrr = (INT32)HSRR0;  // 3
	    cpr = (INT32)CPR0;  // 3
	    chnlMask = CHNL_MASK2;  // 3
	    chnlShift = 12;  // 3
            paramStart = (INT32)CHNL14_PARAM_ADR;  // 4
	    break;
	case 15:
	    *((INT16*)(CFSR0)) &=  FN_MASK1; // clear out chnl 15
	    *((INT16*)(CFSR0)) |=  (tpuFunction << 12); // 1
	    hsqr = (INT32)HSQR0;  // 3
	    hsrr = (INT32)HSRR0;  // 3
	    cpr = (INT32)CPR0;  // 3
	    chnlMask = CHNL_MASK1;  // 3
	    chnlShift = 14;  // 3
            paramStart = (INT32)CHNL15_PARAM_ADR;  // 4
	    break;
    }
    //
    // now enable interrupts if requested to.
    //
    if ( interruptsEnabled ){

        *((INT16*)(CIER)) |= (chnlIntMask); // 2
    }else
        *((INT16*)(CIER)) &= (~chnlIntMask); // 2

}
Tpu::~Tpu()
{
    *((INT16*)(CIER)) &= (~chnlIntMask); // turn off interrupts

}
// -----------------------------------------------------------------
// setSampleRate
//
// This method sets the variable nanoSecondRateTCR1 based on the
// CPU clock speed.  It assumes that PSCK = 0 and the TCR1 pre-
// scaler is set for divide by 1, so total divide is 32.
//
// Author: Mark Giebler
//
long baseF[4] = { 131072, 262144,  524288,  1048576 };
void Tpu::setSampleRate()
{
	unsigned short clockVal;
	unsigned short index;
	long tpuFreq;

	// get the cpu clock control register value
	clockVal = *((unsigned short*) (SYNCR));
	// 1. get the multiplier bits  1
	// 2. use to index into base frequency
	index = (clockVal >> 14); 					// 1
	tpuFreq = baseF[ index ];					// 2
	// 3. get clock multiplier; (bits Y0 - Y5) + 1
	clockVal = ((clockVal >> 8) & 0x03f) + 1;	// 3
	// 4. get cpu frequency
	tpuFreq *= (long) clockVal;					// 4
	// 5. get the TCR1 freq (assume div by 32)
	tpuFreq /= (long) 32;						// 5
	// 6. round up to neares KHz.
	tpuFreq = (tpuFreq + 500L) / 1000L;			// 6
	// 7. get nanoSecond rate of TCR1.
	nanoSecondsTCR1 = 1000000L / tpuFreq;		// 7

}

// -----------------------------------------------------------------
//
//         Name: loadHSQR
//  Description:
//          Load the host sequence register with a 2 bit value for a
//          channel.  See "M68300 Family TPU Reference Manual" for details.
//
//    Arguments:
//          (1) hsqrValue (r)  Value to be written to the hsqr.
//
//      Returns:
//          None.
//
//    Revisions:
//

void Tpu::loadHSQR(INT16 hsqrValue)
{

    *((INT16*)(hsqr)) &= ~chnlMask; // clear our current value
    *((INT16*)(hsqr)) |= (hsqrValue << chnlShift);
}

//
//         Name: loadHSRR
//  Description:
//          Load the host service request register with a 2 bit
//          value for a channel.  See "M68300 Family TPU Reference
//          Manual" for details.
//
//    Arguments:
//          (1) hsrrValue (r)  Value to be written to the hsrr.
//
//      Returns:
//          None.
//
//    Revisions:
//

void Tpu::loadHSRR(INT16 hsrrValue)
{

    *((INT16*)(hsrr)) &= ~chnlMask; // clear our current value
    *((INT16*)(hsrr)) |= (hsrrValue << chnlShift);
}

//
//         Name: loadCPR
//  Description:
//          Load the channel priority register with a 2 bit value for a
//          channel.  See "M68300 Family TPU Reference Manual" for details.
//
//    Arguments:
//          (1) priority (r)  Priority to be written to the cpr.
//
//      Returns:
//          None.
//
//    Revisions:
//

void Tpu::loadCPR(Priorities priority)
{
    *((INT16*)(cpr)) &= ~chnlMask; // clear our current value
    *((INT16*)(cpr)) |= (priority << chnlShift);
}

//
//         Name: loadParameter
//  Description:
//          Load the specified 16 bit parameter within the parameter RAM
//          of the TPU with the given value.  See the "M68300 Family
//          TPU Reference Manual" for details of each function's
//          parameter values.
//
//    Arguments:
//          (1) paramValue (r)  New parameter value.
//          (2) paramNumber (r)  Specific 16 bit paramter to be
//          loaded.  Valid values are 1 through 7.
//
//      Returns:
//          None.
//
//    Revisions:
//

void Tpu::loadParameter(ParamPositions paramNumber, INT16 paramValue)
{
    *((INT16*)(paramStart + paramNumber)) = paramValue;
}

//
//         Name: readParameter
//  Description:
//          Read the specified 16 bit parameter within the parameter RAM
//          of the TPU with the given value.  See the "M68300 Family
//          TPU Reference Manual" for details of each function's
//          parameter values.
//
//    Arguments:
//          (1) paramNumber (r)  Specific 16 bit paramter to be
//          loaded.  Valid values are PARAM_ONE through PARAM_SEVEN.
//
//      Returns:
//          None.
//
//    Revisions:
//

INT16U Tpu::readParameter(ParamPositions paramNumber)
{
    return( *((INT16*)(paramStart + paramNumber)) );
}

//
//         Name: ppwaReadLW
//  Description:
//          Read the lower word of the last accumulation of periods
//          or pulse widths.  This method should be used only for
//          a tpu object being used for the PPWA function.
//          See "M68300 Family TPU Reference Manual" for details.
//
//    Arguments:
//          None.
//
//      Returns:
//          INT16U - lower word of the last accumulation
//
//    Revisions:
//

INT16U Tpu::ppwaReadLW()
{
    INT16U    lowerWord;
    lowerWord = *((INT16*)(paramStart + 0xA));
    return (lowerWord);
}

//
//         Name: ppwaReadUB
//  Description:
//          Read the upper byte of the last accumulation of periods
//          or pulse widths.  It is incremented by the TPU
//          whenever the accumulator overflows.  This method should be
//          used only for a tpu object being used for the PPWA function.
//          See "M68300 Family TPU Reference Manual" for details.
//
//    Arguments:
//          None.
//
//      Returns:
//          BYTE - upper byte of overflow indications
//
//    Revisions:
//
BYTE Tpu::ppwaReadUB()
{
    BYTE    upperByte;
    upperByte = *((BYTE*)(paramStart + 0x9));
    return (upperByte);
}

