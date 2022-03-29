/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:50  $
  $Workfile:   rtclock.cpp  $
*/

#include <dos.h>
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Block.h>
#include <Semaphore.h>
#include <MemBuffer.h>
#include <OpSys.h>
#include <OsTypes.h>
#include <clock.h>
#include <rtClock.h>

#define GET_INTERRUPT 0x35
#define SET_INTERRUPT 0x25
#define CLOCK_INTERRUPT 0x70
#define PIC_1 0x20
#define PIC_2 0xa0
#define RTC 0x70
#define RTC_STATUS_A 10		// address of status register a
#define RTC_STATUS_B 11		// address of status register b
#define RTC_STATUS_C 12		// address of status register c
#define FREQ_BAND 0x20		// time freq of 32,768/sec.
#define ALARM_INTS 0x40		// Interrupt on clock ticks.
#define PIC2_INT 0x4		// allow pic 2 to generate ints
#define RTC_INT 0x1		// allow rt ints (PIC 2)

void interrupt rtClockInt()
{
	os.clockTick();
	asm sti;
}

/* 
RTClock::RTClock
Description:
   Class: RTClock.
   RTClock constructor. Link interrupt routine rtClockInt to AT 
   clock interrupt 0x70, and start clock interrupts.
   Parent class Clock() is called with True specifying that the 
   operating system routine OpSys::clockTick() called by pcClkInt 
   may perform a task switch. Any tasks that become unblocked 
   because of OpSys::clockTick() may be swapped to immediately.
   See Also: OpSys::swapOn()
*/
static const long freqs[] =
{
	0l,32768l,16384l,8192l,4096l,2048l,1024l,512l,256l,
	128l,64l,32l,16l,8l,4l,2l
};
RTClock::RTClock(RTFreq freq) : Clock(OSTrue, freqs[freq])
{
	REGS regs;
	SREGS sregs;

	// save interrupt masks, then mask off clock interrutps.
 	pic1 = inp(PIC_1+1);
	pic2 = inp(PIC_2+1);
	outp(PIC_1+1, pic1 | PIC2_INT);
	outp(PIC_2+1, pic2 | RTC_INT);
	os.swapOff();
	regs.h.ah = GET_INTERRUPT;		// get current int
	regs.h.al = CLOCK_INTERRUPT;		// vector to clock/
	intdosx(&regs, &regs, &sregs);
	oldOff = regs.x.bx;
	oldSeg = sregs.es;
	// Save status a, b registers before modifying them.
	statusA = read(RTC_STATUS_A);
	statusB = read(RTC_STATUS_B);
#ifdef COM
	// When making .com executable (tiny memory model) no segment
	// lookups are allowed. Hence, FP_SEG calls can not be made.
	// use segread() to get current ds instead of ds:: of rtClockInt().
	segread(&sregs);
	sregs.ds = sregs.cs;
#else
	sregs.ds = FP_SEG(rtClockInt);
#endif
	regs.x.dx = FP_OFF(rtClockInt);
	regs.h.ah = SET_INTERRUPT;		// set clock int vector
	regs.h.al = CLOCK_INTERRUPT;		// to clockFun
	intdosx(&regs, &regs, &sregs);
	os.swapOn();
	/*
	 * Set frequency of rt clock. Then set rt clock to interrupt
	 * only on timer ticks.
	*/
	write(RTC_STATUS_A, freq | FREQ_BAND);
	write(RTC_STATUS_B, ALARM_INTS);
	/*
	 * Enable all previously enabled ints + real time clock int's.
	*/
	outp(PIC_1+1, inp(PIC_1+1) & ~PIC2_INT);
	outp(PIC_2+1, inp(PIC_2+1) & ~RTC_INT);
}


/* 
RTClock::~RTClock
Description:
   Class: RTClock.
   RTClock destructor. If no more RTClock objects, then remove 
   rtClockInt from interrupt vector.
*/
RTClock::~RTClock()
{
	REGS regs;
	SREGS sregs;
	unsigned short mask;
	unsigned char newPic1, newPic2;
	os.swapOff();
	// Save current interrupts, then set to disable all interrupts.
	newPic1 = inp(PIC_1+1);
 	newPic2 = inp(PIC_2+1);
	outp(PIC_1+1, newPic1 | PIC2_INT);
	outp(PIC_2+1, newPic2 | RTC_INT);
	// restore status a, b
	write(RTC_STATUS_A, statusA);
	write(RTC_STATUS_B, statusB);
	// Restore original state of real time clock interrupt
	regs.h.ah = SET_INTERRUPT;		// set clock int vector
	regs.h.al = CLOCK_INTERRUPT;		// to clockFun
	regs.x.dx = oldOff;
	sregs.ds = oldSeg;
	intdosx(&regs, &regs, &sregs);
	mask = (newPic2 & ~RTC_INT) | (pic2 & RTC_INT);
	outp(PIC_2+1, mask);
	mask = (newPic1 & ~PIC2_INT) | (pic1 & PIC2_INT);
	outp(PIC_1+1, mask);
	os.swapOn();
}
 

void RTClock::write(short address, unsigned char value)
{
	outp(RTC, address);
	outp(RTC+1, value);
}
int RTClock::read(short address)
{
	outp(RTC, address);
	return(inp(RTC+1));
}

/* 
RTClock::doStart
Description:
   Class: RTClock.
   Start the clock by enabling real time clock interrupts.
*/
void RTClock::doStart()
{
	outp(PIC_1+1, inp(PIC_1+1) & ~PIC2_INT);
	outp(PIC_2+1, inp(PIC_2+1) & ~RTC_INT);
}

/* 
RTClock::doStop
Description:
   Class: RTClock.
   Stop the clock by disabling real time clock interrupts.
*/
void RTClock::doStop()
{
	outp(PIC_1+1, inp(PIC_1+1) | PIC2_INT);
	outp(PIC_2+1, inp(PIC_2+1) | RTC_INT);
}

