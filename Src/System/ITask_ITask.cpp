/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:00  $
  $Workfile:   task.cpp  $
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
ITask::ITask
Description:
   Class ITask.
   ITask constructor.
   Set stack and stack length to passed values.
Parameters:
   stk                 is the user defined external data buffer 
                       used as the stack for this task. This 
                       buffer must not be deleted or reused before 
                       this task is deleted.
   len                 number of bytes in iStack.
   name                optional name of task used for debugging 
                       purposes only.
*/

ITask::ITask(STAKP iStack, unsigned int iStackLen, const char* iName) :
	blockedList(this),
	activeList(this),
	taskList(this),
	timeList(this),
	stack(iStack),
	stackLen(iStackLen/sizeof(STAK)), // convert to # STAK
	name(iName)
{
  objType= ITaskType;
}


/* 
Task::Task
Description:
   Task constructor.
   Construct task. This does not start task execution, but sets it 
   up so that a call to Task::start() will initiate task 
   execution.
*/

/*
1.	Call ITask constructor.
2.	Set objType to Task.
3.	Set task to blockable (default).
4.	Set task priority.
5.	Sets the stack pointer to the bottom or top, depending 
	on whether the stack grows upward (abnormal) or downward (normal).
6.	If CHECKSTACK is defined, and stkFlg is True, initialize all 
	stack locations to a predefined constant for use later to determine
	the stack 'high water' mark.
*/

Task::Task(STAKP iStack, unsigned int iStackLen, short iPriority,
	const char* name) :
	ITask(iStack, iStackLen, name)					//1
{
  objType= TaskType;							//2
  blockable();								//3
  setPriority(iPriority);						//4
#ifdef STACK_GROWS_DOWN
  startOfStack = stack + stackLen;					//5
#else
  startOfStack = stack;							//5
#endif
#ifdef CHECKSTACK
  if ((stack != 0) && (stack != (STAKP) -1))
    {									//6
      unsigned char* sPtr = (unsigned char*) stack;			//6
      unsigned int sLen = stackLen * sizeof(stack[0]);			//6
      while (sLen-- != 0)						//6
	*sPtr++ = STACK_CHECK_VALUE;					//6
    }
#endif
}


/* 
Task::~Task
Description:
   Task destructor.
   Remove task from all linked lists. As far as the operating 
   system is concerned, this task will not exist anymore. This 
   task will not execute any more.
*/

Task::~Task()
{
  os.lock();
  taskList.unlink();
  activeList.unlink();
  blockedList.unlink();
  timeList.unlink();
  os.doSchedule();
  os.unLock();
}

