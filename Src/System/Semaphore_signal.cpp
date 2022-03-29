/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:54  $
  $Workfile:   semap1.cpp  $
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
Semaphore::intSignal
Description:
   Class Semaphore.
   This function is callable from an interrupt routine.
   Signal/increment semaphore. The semaphore value will be
   incremented. Any tasks that are waiting for the semaphore will
   be examined. If the semaphore value that it is waiting for is
   less than or equal to the new semaphore value that task is put
   back onto the active task queue and the semaphore is
   decremented by the value that the task was waiting for.
   Continue checking the oldest task until a task is waiting for
   'more' semaphore than the current value, or no more tasks are
   waiting.
   All blocked tasks are checked and put onto the active list (if
   possible), but no rescheduling will be performed.
   OS_DONE is always returned.
Parameters:
   signals             is the amount to increment the semaphore
                       by.
*/

/*
1. Increment signal count by newSignals. newSignals defaults to 1,
   but can be larger.
2. Iterate through list of tasks that are blocked by this
   semaphore until
	a) no more tasks or
	b) the # of signals that this task is waiting for is greater
	   than the signals left.
3. Decrement signals by the number of signals desired by task that
   has been waiting.
4. Set tasks return value to OS_DONE, meaning that blocked tasks
   request for the semaphore has been fulfilled.
5. Remove task from blocked and timeout list.
6. activate task.
*/

OSRet Semaphore::intSignal(int newSignals)
{
	TaskList* taskList;
	signals += newSignals;															//1
	while (taskList = blockedList.next, taskList != &blockedList)		//2
   {
      ITask* ptr = taskList->task;

      if (ptr->semaphore.signals <= signals)
		{
			signals -= ptr->semaphore.signals;							 		//3
			ptr->blockReturn = OS_DONE;									 		//4
			taskList->unlink();												 		//5
			ptr->timeList.unlink();											 		//6
			ptr->activate();													 		//6
		}
      else
			break;
   }
  return(OS_DONE);
}

/*
Semaphore::signal
Description:
   Class Semaphore.
   Signal/increment semaphore. The semaphore value will be
   incremented. Any tasks that are waiting for the semaphore will
   be examined. If the semaphore value that it is waiting for is
   less than or equal to the new semaphore value that task is put
   back onto the active task queue and the semaphore is
   decremented by the value that the task was waiting for.
   Continue checking the oldest task until a task is waiting for
   'more' semaphore than the current value, or no more tasks are
   waiting.
   All blocked tasks are checked and put onto the active list (if
   possible) before any rescheduling is performed. No task will
   actually be executed until the process of checking the tasks is
   complete.
   OS_DONE is always returned.
Parameters:
   signals             is the amount to increment the semaphore
                       by.
*/

/*
1. Check that semaphore has been initialized (debug only).
2. Lock out any interrupts.
3. Unblock all tasks waiting on this semaphore, if
	newCount is high enough.
4. Schedule tasks if any tasks were unblocked.
5. Reenable interrupts.
*/

OSRet Semaphore::signal(int newSignals)
{
	checkInit();												//1
	os.lock();													//2
	intSignal(newSignals);                  			//3
	os.doSchedule();											//4
	os.unLock();												//5
	return(OS_DONE);
}

