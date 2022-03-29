/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision:   2.1  $
  $Modtime:   01 May 1993 09:34:24  $
  $Workfile:   vclock.cpp  $
*/
#include <opsys.h>
#include <vclock.h>
#include <ossun.h>
#define USECS 100000
#define SECS  0
/* 
VClock::timerInt
Description:
   This is the routine called when the interval timer signal is 
   received. It calls OpSys::clockTick() to process the clock 
   tick.
   This routine must never be called directly by the user.
*/
void vtimerInt()
{
	os.clockTick();
}

/* 
VClock::VClock
Description:
   VClock constructor. Set up sun real time interval timer to 
   generate ITIMER_VIRTUAL signal 10 times per second, and set up 
   signal handler to call OpSys::clockTick() at every signal.
*/
VClock::VClock() : Clock(False, 10)
{
	static sigvec newVec = , SIGVTALRM, 0};
	currTime.it_interval.tv_usec = USECS;
	currTime.it_interval.tv_sec = SECS;
	currTime.it_value.tv_usec = USECS;
	currTime.it_value.tv_sec = SECS;
	sigblock(sigmask(SIGVTALRM));
	sigvec(SIGVTALRM, &newVec, 0);
	setitimer(ITIMER_VIRTUAL, &currTime, 0);
	start();
}

/* 
VClock::~VClock
Description:
   VClock destructor. If no more VClock objects, then remove 
   vTimerInt from interrupt vector.
*/
typedef void (*VFCN)();
VClock::~VClock()
{
	static sigvec newVec = _DFL, SIGVTALRM, 0};
	stop();
	sigvec(SIGVTALRM, &newVec, 0);
}
 

/* 
VClock::doStart
Description:
   Start the clock by installing the ITIMER_VIRTUAL signal 
   handler, so that vTimerInt() gets called at every virtual timer 
   interrupt.
   See Also: VClock::doStop()
*/
void VClock::doStart()
{
	int mask;
	os.swapOff();
	mask = sigblock(sigmask(SIGVTALRM));
	sigsetmask(mask & ~sigmask(SIGVTALRM));
	os.swapOn();
}

/* 
VClock::doStop
Description:
   Stop the clock by disabling real time clock signals.
   See Also: VClock::doStart()
*/
void VClock::doStop()
{
	int mask = sigblock(sigmask(SIGVTALRM));
}

