/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.
*/

/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:52  $
  $Workfile:   break.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <MemBuffer.h>
#include <BitFlag.h>
#include <Thread.h>
#include <opSys.h>
#include <break.h>
#include <dos.h>

#define GET_INTERRUPT 0x35
#define SET_INTERRUPT 0x25
#define BREAK_INTERRUPT 0x23

/* 
USBreak::doBreak
Description:
   Class: USBreak.
   This is called from the DOS interrupt that occurs when the user 
   pressed ctl-c. It signals OpSys to exit. OpSys will quit at the 
   next task switch.
*/

void interrupt breakInt()
{
	os.exit(-1);
	asm sti;
}



/* 
USBreak::USBreak
Description:
   Class: USBreak.
   This is the User Break (USBreak) constructor. Install the ctl-c 
   interrupt handler.
*/

USBreak::USBreak()
{
	if (breaks++ == 0)
	{
		REGS regs;
		SREGS sregs;

		os.swapOff();
		regs.h.ah = GET_INTERRUPT;		// get current int
		regs.h.al = BREAK_INTERRUPT;		// vector to break
		intdosx(&regs, &regs, &sregs);
		oldOff = regs.x.bx;
		oldSeg = sregs.es;

#ifdef COM
		// When making .com executable (tiny memory model) no segment
		// lookups are allowed. Hence, FP_SEG calls can not be made.
		// use segread() to get current ds instead of ds:: of
		// breakInt
		segread(&sregs);
		sregs.ds = sregs.cs;
#else
		sregs.ds = FP_SEG(breakInt);
#endif
		regs.x.dx = FP_OFF(breakInt);
		regs.h.ah = SET_INTERRUPT;		// set clock int vector
		regs.h.al = BREAK_INTERRUPT;		// to break
		intdosx(&regs, &regs, &sregs);
		os.swapOn();
	}
}


/* 
USBreak::~USBreak
Description:
   Class: USBreak.
   User Break (USBreak) destructor. If no more breaks are 
   installed, the remove ctl-c interrupt handler.
*/

USBreak::~USBreak()
{
	if (--breaks == 0)
	{
		REGS regs;
		SREGS sregs;

		regs.h.ah = SET_INTERRUPT;
		regs.h.al = BREAK_INTERRUPT;
		regs.x.dx = oldOff;
		sregs.ds = oldSeg;
		intdosx(&regs, &regs, &sregs);
	}
}



unsigned int USBreak::oldSeg = 0;
unsigned int USBreak::oldOff = 0;
unsigned short USBreak::breaks = 0;
