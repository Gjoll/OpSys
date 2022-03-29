/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:20  $
  $Workfile:   bitflag1.cpp  $
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

/*
BitFlag::intSignal
Description:
   Class BitFlag.
	This is callable from an interrupt routine.
   Set and/or Clear some bits in bitflag. After operation, check
   if any of the tasks that are blocked waiting for a specific
   configuration of bits in bitflag can now be unblocked. If so,
   remove those tasks from the BitFlags BLOCKED linked list and
   put it back onto the active task queue. No task rescheduling/swapping
   is performed.
   This task always returns OS_DONE.
Parameters:
   set                 are the bit to turn on in the bit flag.
   clr                 are the bit to turn off in the bitflag.

*/
/*
Implementation
1.	Change bits as specified by set and clr.
2.	If more bits have been set, then check to see if the tasks
	waiting for certain bits to be set can now be unblocked.
3.	Iterate through all tasks blocked by this BitFlag.
4.	If all the bits that the task is waiting for are set, or it
	one or more of the bits that the task is waiting for is set
	and the task specified to only wait for one or more, not all
	the bits, then unblock task.
5.	Remove task from BitFlags blocked list.
6.	Remove task from timeout list.
7.	Put task onto active list.
8.	Mark completion of that tasks wait as done. eg it worked.
9.	Get next task on blocked list.
*/

OSRet BitFlag::intSignal(unsigned long set, unsigned long clr)
{
	bits |= set;																	//1
	bits &= ~clr;																	//1
	if (set != 0)																	//2
	{
		TaskList* listPtr = blockedList.next;
		while (listPtr != &blockedList)										//3
		{
			Task* ptr = (Task*) listPtr->task;
			TaskList* nextPtr = listPtr->next;
			long waitBits = ptr->bitFlag.bits;
			if (																		//4
	      	((bits & waitBits) == waitBits) ||
	      	(
	       		((bits & waitBits) != 0) &&
	       		(ptr->bitFlag.type == OS_ONE)
	       	)
				)
         {
				listPtr->unlink();												//5
				ptr->timeList.unlink();											//6
				ptr->activate();													//7
				ptr->blockReturn = OS_DONE;									//8
			}
			listPtr = nextPtr;													//9
		}
	}
   return(OS_DONE);
}

/*
BitFlag::signal
Description:
   Class BitFlag.
   Set and/or Clear some bits in bitflag. After operation, check
   if any of the tasks that are blocked waiting for a specific
   configuration of bits in bitflag can now be unblocked. If so,
   remove those tasks from the BitFlags BLOCKED linked list and
   put it back onto the active task queue.
   This task always returns OS_DONE.
Parameters:
   set                 are the bit to turn on in the bit flag.
   clr                 are the bit to turn off in the bitflag.

*/
/*
Implementation
1.	Verify that the bits that are to be set and cleared are
	disjoint. That is bit 1 is not to be set and cleared.
2.	Verify that BitFlag is initialized.
3.	Disable interrupts.
4.	Unblock all tasks that are waiting for these signals.
5.	Reschedule tasks, if any tasks were unblocked.
6.	Enable interrupts.
7.	BitFlag::signal() always returns OS_DONE.
*/

OSRet BitFlag::signal(unsigned long set, unsigned long clr)
{
  assert((set & clr) == 0);													//1
  checkInit();																		//2
  os.lock();																		//3
  intSignal(set, clr);															//4
  os.doSchedule();																//5
  os.unLock();																		//6
  return(OS_DONE);																//7
}

