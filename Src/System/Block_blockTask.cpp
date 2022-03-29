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
  $Workfile:   block3.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <MailBox.h>
 
/* 
Block::blockTask
Description:
   Class Block.
   Remove current task from active task list and put it onto the 
   blocked task list. Location on the block list is either first 
   in first out, or ordered by task priority (highest first). Task 
   ordering is selected at construction time by the flag settings. 
   OS_PRIORITY -> ordered by task priority, OS_FIFO -> first in 
   first out.
   This task returns the task completion status when the task 
   becomes unblocked.
   Value               Meaning
   OS_DONE             Block operation operated correctly.
   OS_BLOCKERR         The calling task is marked as unblockable.
   OS_TIMEOUT          The calling task timed  out waiting for 
                       data.
   OS_DELETED          The block object was deleted while the 
                       calling task was blocked.
Parameters:
   timeout             is timeout value specifying the maximum 
                       amount of time that the task should wait to 
                       become unblocked.
*/

/*
1.	if timeout is zero (timeout immediately) then return timeout.
2.	Remove current task from the active task list and 
	reschedule to another task.
3.	Find place in blocked linked list to insert task. If PRIORITY 
	blocker, then find spot ordered by task priority, otherwise 
	if FIFO put at end of list.
4.	After being reawakened return to calling task 
	with the completion status.
5.	if current task is marked as not being blockable, then
	return so.
6.	Return completion value.
*/

OSRet Block::blockTask(OSTime timeout)
{
	OSRet retVal;
	assert(os.schFlag & LOCKED);	// verify interrupts off.

	if (timeout == OS_ZEROTIMEOUT)									//1
		retVal = OS_TIMEOUT;
	else
	{
		register Task* tPtr = (Task*) os.currentTask;
		if (
			(tPtr->tFlags & OS_BLOCKABLE) &&
			((os.schFlag & (NOSCHEDSWAP | INITIALIZING)) == 0)
			)
		{															//2
			TaskList* taskList = blockedList.next;
			tPtr->blocker = this;
			tPtr->activeList.unlink();
			if (!(flags & OS_FIFO))
			{														//3
				while ((taskList != &blockedList) &&
						(taskList->task->priority >= tPtr->priority))
					taskList = taskList->next;
			}
			tPtr->blockedList.link(taskList);
			if (timeout != OS_NOTIMEOUT)
				tPtr->doTimeout(timeout);
			os.doSchedule();
			retVal = tPtr->blockReturn;								//4
		} else
			retVal = OS_BLOCKERR;									//5
	}
	return(retVal);													//6
}

