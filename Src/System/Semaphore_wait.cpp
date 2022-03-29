/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:56  $
  $Workfile:   semap2.cpp  $
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
Semaphore::wait
Description:
   Class Semaphore.
   Check if semaphore value is the same or higher as the passed 
   value. If it is not, wait until it is. When it is, decrement 
   the count by the passed value and return.
   Tasks that are waiting are removed from the active task list 
   and wait in the order that they are received.
   An optional timeout can be specified to limit the time that the 
   task will remain blocked.
   The following are the values that can be returned from 
   Semaphore::wait().
   OS_DONE                 The semaphore had the desired count.
   OS_TIMEOUT          The timeout period expired.
   OS_BLOCKERR         The calling task is not blockable, and can 
                       not be removed from the active task queue.
   OS_DELETED          The Semaphore object that the task was 
                       waiting for was deleted.
Parameters:
   signals             is the number of semaphore counts that the 
                       caller is requesting/waiting for.
   timeout             is an optional timeout value to specify the 
                       maximum number of clock ticks to wait.
*/

/*
1. check that semaphore has been initialized.
2. Lock out interrupts.
3. If the current task would be placed at the front of the blocked list and
   there are as many signals in the semaphore as requested then
   decrement signals and return immediately. The current task would be
   placed in the front of the blocked list if a) there are no other tasks
   in the blocked list or b) the semaphore is a priority semaphore and the
   current task is of higher priority than the next task on the blocked list.
4. Store the requested number of signals in tasks memory
5. Block current task
6. reenable interrupts.
7. Return status.
*/

OSRet Semaphore::wait(int waitSignals, OSTime timeout)
{
  OSRet retVal;
  checkInit();								//1
  os.lock();								//2

  TaskList* firstBlocked = blockedList.next;

  if (									//3
      (
       (firstBlocked == &blockedList) || 
       (
	(!(flags & OS_FIFO)) &&
	(firstBlocked->task->priority < os.currentTask->priority) 
	)
       ) && 
      (signals >= waitSignals)
      )
    {
      signals -= waitSignals;						//3
      retVal = OS_DONE;							//3
    }
  else
    {
      os.currentTask->semaphore.signals = waitSignals;			//4
      retVal = blockTask(timeout);					//5
    }
  os.unLock();								//6
  return(retVal);							//7
}
