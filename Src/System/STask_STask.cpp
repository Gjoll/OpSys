/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:58  $
  $Workfile:   stask.cpp  $
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
STask::STask
Description:
   Class STask.
   STask constructor.
   Construct STask. This does not start task execution, but sets 
   it up so that a call to STask::start will initiate task 
   execution.
*/

STask::STask(unsigned int iStackLen, short iPriority, const char* name) :
	Task(allocStack(iStackLen), iStackLen, iPriority, name)
{
}


/* 
STask::~STask
Description:
   Class STask.
   STask destructor.
*/

/*
1. Disallow task swapping, otherwise Task::~Task() will attempt 
   to reschedule before we have freed the stack.
2. Free the stack for reuse.
3. Allow task scheduling.
4. Reschedule.
*/

STask::~STask()
{
  os.swapOff();								// 1
  os.stackAlloc.put((void*) stack);					// 2
  os.swapOn();								// 3
  os.schedule();							// 4
}

