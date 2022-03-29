/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:08  $
  $Workfile:   task5.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
// ITask* taskPtr
// Pointer to the task that is currently being started.
// This is set by start() and read by startTask1().
static ITask* taskPtr;

/* 
ITask::start
Description:
   Class ITask.
   Start execution of the task. This should be called once when 
   execution of the task is to be started. It should not be called 
   after execution has started and before execution has completed 
   or stopped.
   The following are the values that can be returned from this 
   function.
   OS_DONE             Operation worked. Task started.
   OS_ERROR            Task not started. Task setup did not work 
                       correctly. Check that stack was allocated 
                       properly.
*/

/*
1.	Verify object has been constructed (debug only).
2.	Lock out any interrupts that will modify linked lists.
3.	Put task onto active list ordered by priority.
4.	Store pointer to this for later use by startTask1.
5.	Set the current task pointer to this, as this task will 
	be starting shortly.
6.	Call assembly routine startTask. That will save the current 
	registers onto the current task, store the current stack 
	pointer, set the stack pointer to the stack in the task 
	that is being started, and then immediately swap back to the
	current task.
7.	Reschedule tasks, just in case task started is of higher priority 
	than the current task.
8.	When startTask returns, reenable interrupts and return to 
	current caller.
*/

OSRet ITask::start()
{
  checkInit();								// 1
  if ((stack != 0) && (stack != (STAKP) -1))
    {
      os.lock();							// 2.
      activate();							// 3.
      taskPtr = this;							// 4
      startTask(&os.currentTask->stackPtr, startOfStack);		// 6
      os.doSchedule();							// 7
      os.unLock();	// trust me, this belongs here ...		// 8
      return OS_DONE;
    }
  return OS_ERROR;
}


/* 
startTask1
Description:
   startTask1() should NEVER be called by the user !
   This is called from the assembly function startTask, which is 
   called from start().
   When execution starts here, the stack is the stack of the task 
   that has been started. No return address is on the stack! The 
   routine that resets the stack pointer (sp), startTask, did a 
   jump to startTask1. Hence this routine can never exit via a 
   return instruction.
Implementation:
   1.  Save pointer to task object that has just been started. 
      Store this on stack, as global variable taskPtr will be 
      overwritten after schedule() call or unLock() call.
   2.  Swap back to task that started this task. Now that this 
      task exists on all the correct lists, has a correct stack, 
      and can be swapped in and out as its priority comes due.
   3.  When os.swap() returns, then this task is highest priority 
      task. Call unLock() to reenable the interrupts for this 
      task.
   4.  Call virtual run method for task just created.
   5.  If run() returns (mostly wont), then stop this task. Remove 
      it from all lists so that it will not be executed any more.
*/

void startTask1()
{
  ITask* thisTaskPtr = taskPtr;						// 1
  swap(&thisTaskPtr->stackPtr, os.currentTask->stackPtr);		// 2
  os.unLock();								// 3
  thisTaskPtr->run();							// 4
  thisTaskPtr->stop();							// 5
}

