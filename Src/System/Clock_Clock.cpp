/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:44  $
  $Workfile:   clock.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <OsTypes.h>
#include <clock.h>

/* 
Clock::Clock
Description:
   Class Clock.
   Clock constructor. There can only be ONE object of class Clock, 
   or derived from class Clock, at any one time!
   Set the routine OpSys::clockTick() to allow/disallow timer 
   interrupt task switching. At every clock tick, OpSys::clockTick 
   checks to see if any tasks have become unblocked because of 
   timeouts expiring. If task switching is enabled, then 
   OpSys::schedule() is called from OpSys::clockTick to perform a 
   task switch to a new, higher priority task BEFORE the interrupt 
   has completed. Hence the interrupt must reset all necessary 
   hardware before calling OpSys::clockTick, as OpSys::clockTick 
   may not return for many clock ticks.
   Call the Clock constructor with True to allow timer task 
   switches, False to not allow timer interrupt task switching.
Parameters::
   flag                determines if a task switch is allowed 
                       during the clock interrupt. True means 
                       allowed, False not.
*/

Clock* Clock::current;
Clock::Clock(Bool flag, unsigned long ticksPSec) :
	hertz(ticksPSec),
	started(OSFalse)
{
  assert (current == 0);
  current = this;
  if (flag == OSTrue)
    os.timerSwapOn();
  else os.timerSwapOff();
}


/* 
Clock::~Clock
Description:
   Clock destructor. There can only be ONE object of class Clock, 
   or derived from class Clock, at any one time!
   Clear pointer to current clock.
*/

Clock::~Clock()
{
	current = 0;
}

