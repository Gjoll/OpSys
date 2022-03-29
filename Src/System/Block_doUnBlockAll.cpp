/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:40  $
  $Workfile:   block1.cpp  $
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

/* 
Block::doUnBlockAll
Description:
   Class Block.
   Unblock all tasks waiting on this Block object. All tasks will 
   be placed back onto the active task queue, and will be executed 
   when their priority is highest.
   Since OpSys::lock and OpSys::unLock are NOT called by this 
   routine, they MUST be called by the calling routine to lock out 
   interrupts for the duration of doUnBlockAll().
*/

/*
1.	Iterate through all tasks on the blocked list of this block.
2.	Remove tasks from TIMEOUT list and BLOCKED list.
3.	Set return value to task to DELETED.
4.	Put task back onto active task list.
5.	If any tasks were activated, then call os.schedule() to 
	do any necessary rescheduling.
*/
void Block::doUnBlockAll() 
{
  TaskList* listPtr;
  while (listPtr = blockedList.next,
	 listPtr != &blockedList) 					// 1
    {
      ITask* tPtr = listPtr->task;					// 2
      tPtr->blockedList.unlink();					// 2
      tPtr->timeList.unlink();						// 2
      tPtr->blockReturn = OS_DELETED;					// 3
      tPtr->activate();							// 4
    }
  os.doSchedule();							// 5
}

