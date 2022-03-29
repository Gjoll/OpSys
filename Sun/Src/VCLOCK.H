/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision:   2.1  $
  $Modtime:   01 May 1993 09:34:28  $
  $Workfile:   vclock.h  $
*/
#ifndef VCLOCK_H
#define VCLOCK_H
#include <sys/time.h>
#include <signal.h>
#include <clock.h>
#include <osconfig.h>
#include <ostypes.h>
/* 
VClock
Description:
   This class implements the Virtual interval timer under the Sun 
   3 OS 4.0.3 operating system.
   The virtual interval timer will cause OpSys timer resolution to 
   be 10 ticks/second. These ticks will be in virtual process 
   time, That is, in time that the process is actually running. 
   The clock will not run when the process is not running.
   This clock will not cause the currently running task to be 
   preempted. Rather it will unblock any tasks that are waiting on 
   a timeout condition. They will not become activated until the 
   next task switch.
   When this clock is destroyed, the SIGVTALRM is left blocked, 
   and the default SIGVTALRM signal handler is reinstalled. If a 
   signal handler other than the default was installed, it will 
   not be reinstalled at VClock destruction.
Data:
   currTime            This is the current value loaded into the 
                       virtual time clock interval registers.
Methods:
   VClock              Constructor.
   ~VClock             Destructor.
   start               Start real time clock.
   stop                Stop real time clock.
*/
class VClock : public Clock {
       friend void vtimerInt();
private:
 	sigvec oldVec;
	itimerval currTime;
	itimerval origTime;
	void doStart();
	void doStop();
public:
	VClock();
	~VClock();
};

#endif
