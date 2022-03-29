/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.
*/

/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:54  $
  $Workfile:   pcclock.cpp  $
*/

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
#include <pcClock.h>
#include <dos.h>
#include <stdio.h>

#define GET_INTERRUPT 0x35
#define SET_INTERRUPT 0x25
#define CLOCK_INTERRUPT 0x1c

void interrupt pcClockInt()
{
	asm sti;
	os.clockTick();
}

/* 
PCClock::PCClock
Description:
   Class: PCClock.
   PCClock constructor. Link interrupt routine pcClkInt to PC 
   clock interrupt 0x1c, and start clock interrupts.
   Parent class Clock() is called with False specifying that the 
   operating system routine OpSys::clockTick() called by pcClkInt 
   will not perform a task switch. Any tasks that become unblocked 
   because of OpSys::clockTick() will not be swapped to, rather 
   they will be swapped to at the next task switch. Since this is 
   a dos interrupt routine, it is not know if DOS would allow this 
   interrupt to swap to another task, execute for some period of 
   time, possible having another clock interrupt, then return to 
   the original interrupt. Hence, it is not allowed.
*/

PCClock::PCClock() : Clock(OSFalse, 18l)
{
	REGS regs;
	SREGS sregs;

	regs.h.ah = GET_INTERRUPT;		// get current int
	regs.h.al = CLOCK_INTERRUPT;		// vector to clock/
	os.swapOff();
	intdosx(&regs, &regs, &sregs);
	os.swapOn();
	oldOff = regs.x.bx;
	oldSeg = sregs.es;
	start();
}


/* 
PCClock::~PCClock
Description:
   Class: PCClock.
   PCClock destructor. If no more PCClock objects, then remove 
   pcClkInt from interrupt vector.
*/

PCClock::~PCClock()
{
	stop();
}


 
/* 
PCClock::doStart
Description:
   Class: PCClock.
   Start the clock by setting the interrupt vector to point to 
   interrupt address pcClockInt.
*/

void PCClock::doStart()
{
	REGS regs;
	SREGS sregs;

#ifdef COM
	segread(&sregs);
	sregs.ds = sregs.cs;
#else
	sregs.ds = FP_SEG(pcClockInt);
#endif
	regs.x.dx = FP_OFF(pcClockInt);
	regs.h.ah = SET_INTERRUPT;		// set clock int vector
	regs.h.al = CLOCK_INTERRUPT;		// to clockFun
	os.swapOff();
	intdosx(&regs, &regs, &sregs);
	os.swapOn();
}



/* 
PCClock::doStop
Description:
   Class: PCClock.
   Stop clock interrupts. This removes the interrupt routine 
   pcClockInt from the interrupt vector 0x1c, and puts the 
   original interrupt vector back.

*/

void PCClock::doStop()
{
	REGS regs;
	SREGS sregs;

	// Restore original state of real time clock interrupt
	regs.h.ah = SET_INTERRUPT;		// set clock int vector
	regs.h.al = CLOCK_INTERRUPT;		// to clockFun
	regs.x.dx = oldOff;
	sregs.ds = oldSeg;
	os.swapOff();
	intdosx(&regs, &regs, &sregs);
	os.swapOn();
}


