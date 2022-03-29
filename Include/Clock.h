/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:34  $
  $Workfile:   clock.h  $
*/
#ifndef CLOCK_H
#define CLOCK_H
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <OsTypes.h>

/* 
Clock
Description:
   Class Clock is the base class for all timer interrupt objects 
   defined for OpSys. It initializes schFlag to allow/disallow 
   task switching while in OpSys::clockTick (clock interrupt 
   routine). It also creates the virtual start/stop clock methods.
   This class is of interest only to the user who is attempting to 
   create a new Clock/Timer class.
*/

class Clock
{
 private:
 protected:
  Bool started;
  Clock(Bool timerSwaps, unsigned long);
  ~Clock();
  virtual void doStop() = 0;
  virtual void doStart() = 0;
 public:
  const unsigned long hertz;
  static Clock* current;
  void stop();
  void start();
};

#endif
