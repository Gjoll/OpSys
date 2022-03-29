/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:12  $
  $Workfile:   task9.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>

/* 
ITask::setPriority
Description:
   Class ITask.
   Set/Change the priority of a task.
*/
void ITask::setPriority(short newPriority)
{
  assert((newPriority <= MAX_PRIORITY) &&
	 (newPriority >= MIN_PRIORITY));
  doSetPriority(newPriority & 0xff);
}


