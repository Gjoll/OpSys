/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision:   2.1  $
  $Modtime:   01 May 1993 09:34:30  $
  $Workfile:   rclock.h  $
*/
#ifndef RCLOCK_H
#define RCLOCK_H
#include <sys/time.h>
#include <signal.h>
#include <clock.h>
#include <osconfig.h>
#include <ostypes.h>
/* 
RClock
Description:
   This class implements the Real Time clock under the Sun 3 OS 
   4.0.3 operating system.
   The real time clock will cause OpSys timer resolution to be 10 
   ticks/second. These ticks will be in real time, not virtual 
   process time!
   This clock will not cause the currently running task to be 
   preempted. Rather it will unblock any tasks that are waiting on 
   a timeout condition. They will not become activated until the 
   next task switch.
   When this clock is destroyed, the SIGALRM is left blocked, and 
   the default SIGALRM signal handler is reinstalled. If a signal 
   handler other than the default was installed, it will not be 
   reinstalled at RClock destruction.
Data:
   currTime            This is the current value loaded into the 
                       virtual time clock interval registers.
Methods:
   RClock              Constructor.
   ~RClock             Destructor.
   start               Start real time clock.
   stop                Stop real time clock.
*/
class RClock : public Clock {
       friend void rtimerInt();
private:
	itimerval currTime;
	void doStart();
	void doStop();
public:
	RClock();
	~RClock();
};

#endif
