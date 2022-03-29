/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:10  $
  $Workfile:   task7.cpp  $
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
ITask::stop
Description:
   Class ITask.
   Stop execution of task. Remove task from active task list. This
   task will not get any more CPU time to execute. If task calls
   stop on itself, then this function will never return.
*/

/*
1.	Check that stack has not overflowed. If stackLen == 0, then
	task is idle task, whose stack was never initialized as it
	was in use by main at the start of the program.
2.	Check that task in not on timeout queue. This should never happen.
3.	If task is unblockable, then don't remove from linked lists,
	just stay in infinite loop. Otherwise remove from all
	active lists.
*/
void ITask::stop()
{
	assert((stackLen == 0) || (stackFree(MIN_STACK) >= MIN_STACK));	//1
	/*assert(timeList.next == &timeList);*/							//2
	/*assert(timeList.last == &timeList);*/							//2

	if (tFlags & OS_BLOCKABLE)										//3
	{
		os.lock();
		activeList.unlink();
		timeList.unlink();
		blockedList.unlink();
		taskList.unlink();
		os.doSchedule();
		os.unLock();
	}
}

