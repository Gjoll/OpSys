/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:14  $
  $Workfile:   opsys3.cpp  $
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
OpSys::doSchedule
Description:
   Class OpSys.
   This routine is called to find the highest priority task (the 
   first task on the active list, they are ordered in priority) 
   and execute it. If it is not the currently running task, then 
   swap() tasks to start executing the new task and set 
   currentTask to the new task.
   Swap will save the registers on the current tasks stack, save 
   the current stack pointer in current->stackPtr, set the stack 
   pointer to the new tasks previously saved stack pointer, 
   restore the registers from that stack and return to the routine 
   that caused that task to be removed from the active list.
   Later, when this task becomes reactivated, swap will return to 
   this task.
*/

void OpSys::doSchedule()
{
	assert(os.schFlag & LOCKED);	// verify interrupts off.

	if (!(os.schFlag & (INITIALIZING | NOSCHEDSWAP)))
	{
		ITask* tPtr = os.activeList.next->task;
		ITask* current = os.currentTask;
		if (current != tPtr)
		{
			os.currentTask = tPtr;
#ifndef NDEBUG
			os.swapCount += 1;
#endif
			swap(&current->stackPtr, tPtr->stackPtr);
		}
	}
}

