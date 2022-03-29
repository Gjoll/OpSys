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
  $Workfile:   rclock.cpp  $
*/
#include <opsys.h>
#include <rclock.h>
#define USECS 100000
#define SECS  0
/* 
RClock::rtimerInt
Description:
   This is the routine called when the interval timer signal is 
   received. It calls OpSys::clockTick() to process every clock 
   tick.
*/
void rtimerInt()
{
	os.clockTick();
}

/* 
RClock::RClock
Description:
   RClock constructor. Set up sun real time interval timer to 
   generate signal 10 times per second, and set up signal handler 
   to call OpSys::clockTick() at every signal.
*/
RClock::RClock() : Clock(False, 10)
{
	static sigvec newVec = , SIGALRM, 0};
	currTime.it_interval.tv_usec = USECS;
	currTime.it_interval.tv_sec = SECS;
	currTime.it_value.tv_usec = USECS;
	currTime.it_value.tv_sec = SECS;
	sigblock(sigmask(SIGALRM));
	sigvec(SIGALRM, &newVec, 0);
	setitimer(ITIMER_REAL, &currTime, 0);
	start();
}

/* 
RClock::~RClock
Description:
   RClock destructor. If no more RClock objects, then remove 
   rtClokInt from interrupt vector.
*/
typedef void (*VFCN)();
RClock::~RClock()
{
	static sigvec newVec = _DFL, SIGALRM, 0};
	stop();
	sigvec(SIGALRM, &newVec, 0);
}
 

/* 
RClock::doStart
Description:
   Start the clock by installing the ITIMER_REAL signal handler, 
   so that rTimerInt() gets called at every real time timer 
   interrupt.
   See Also: RClock::doStop()
*/
void RClock::doStart()
{
	int mask;
	os.swapOff();
	mask = sigblock(sigmask(SIGALRM));
	sigsetmask(mask & ~sigmask(SIGALRM));
	os.swapOn();
}

/* 
RClock::doStop
Description:
   Stop the clock by disabling virtual clock signals.
   See Also: RClock::doStart()
*/
void RClock::doStop()
{
	int mask = sigblock(sigmask(SIGALRM));
}

