/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:18  $
  $Workfile:   opsys7.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <BitFlag.h>
#include <Pipe.h>
#include <OsTypes.h>

/* 
OpSys::clockTick
Description:
   Class OpSys.
   This routine is called whenever a clock interrupt routine 
   occurs. It increments the number of clock ticks, and searches 
   through the TIMEOUT list to see if the timeouts for any tasks 
   have expired. If so then it puts the tasks back onto the active 
   list. If schFlag is set to allow rescheduling from a timer 
   interrupt, OpSys::schedule is called to start execution at the 
   highest priority unblocked task.
   Rescheduling can cause a problem. The interrupt routine MUST 
   have reinitialized the clock interrupt, and interrupts, because 
   clockTick can cause a task switch and not return for some time.
*/

/*
1.	Check if interrupts/ clock ticks are currently locked. If not
	continue.
2.	Increment clock tick counter.
3.	Lock out interrupts while searching through the 
	task timeout list for any timeouts that have occurred.
4.	Search through all elements of the timeout list 
	until a) no more elements, or b) the next elements 
	timeout has not expired. All tasks on the timeout list 
	are ordered by their timeout expiration time, 
	earliest first, latest last.
5.	For all tasks whose timeout has occurred, remove 
	from the timeout list and the blocked list, and put 
	onto the active list. Get new next pointer and set 
	flag to call scheduler later.
6.	If task swapping is enabled, then run any scheduled tasks.
7.	Reenable interrupts. Return to clock interrupt function.
8	If currently locked, record the fact that a tick occurred. 
	OpSys::unLock() will call this routine again to execute this clock 
	tick when interrupts are unlocked.
*/

void OpSys::clockTick()
{
	if (locked() == OSFalse)												// 1
   {
   	os.tickCount += 1;													// 2
      lock();																	// 3
      {
			TaskList* listPtr;
			while ((listPtr = os.timeList.next,
						listPtr != &os.timeList) &&						// 4
					(listPtr->task->timeOut -os. tickCount <= 0))
			{
				ITask* tPtr = listPtr->task;
				tPtr->timeList.unlink();									// 5
				tPtr->blockedList.unlink();
				tPtr->blockReturn = OS_TIMEOUT;
				tPtr->activate();
			}
			if (os.schFlag == 0)									  			// 6
				doSchedule();
		}
		unLock();																// 7
	}
   else os.ticks += 1;														// 8
}

