/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:06  $
  $Workfile:   task4.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Semaphore.h>
#include <OpSys.h>

/* 
ITask::sleep
Description:
   Class ITask.
   Put task to sleep for timeout clock ticks, and swap to the next 
   highest priority active task. When the timeout period is up 
   this task will be placed onto the active task again.
   When it is the highest priority task then Opsys::.schedule will 
   return and execution can continue.
   This task will block a task permanently if a clock interrupt 
   routine is not installed that periodically calls 
   OpSys::clockTick.
Parameters:
   timeout             is the number of clock ticks to sleep for.
*/

void ITask::sleep(OSTime timeout)
{
  checkInit();
  os.lock();
  doTimeout(timeout);
  os.doSchedule();
  os.unLock();
}

