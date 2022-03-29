/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:04  $
  $Workfile:   task2.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Semaphore.h>
#include <OpSys.h>

/* 
ITask::doTimeout
Description:
   Class ITask.
   Put this task onto TIME task list, ordered by the timeout 
   interval and remove the task from the ACTIVE task list. Tasks 
   with smaller timeouts shall come first on the timeout list, 
   longer timeouts later.
   The timeout period that is stored with the task is an absolute 
   time that the task should be awakened on. The timeout period 
   'timeout' passed is a relative time, eg 10 clock ticks from 
   now. Hence to convert between the 2 times, add or subtract the 
   current time.
Parameters:
   timeout                 is the timeout value.
*/

void ITask::doTimeout(OSTime timeout)
{
  assert(os.schFlag & LOCKED);	// verify os.lock() called prior.
  checkInit();
  TaskList* listPtr = os.timeList.next;

  activeList.unlink();

  while (
	 (listPtr != &os.timeList) &&
	 (listPtr->task->timeOut - os.now() <= timeout)
	 )
    listPtr = listPtr->next;
  timeOut = timeout + os.now();
  timeList.link(listPtr);
}

