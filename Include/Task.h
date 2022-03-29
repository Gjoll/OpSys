/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.
*/

/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:26  $
  $Workfile:   Task.h  $
*/
#ifndef TASK_H
#define TASK_H
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <OsTypes.h>
#define MAX_PRIORITY 255
#define MIDHI_PRIORITY 192
#define MID_PRIORITY 128
#define MIDLO_PRIORITY 64
#define MIN_PRIORITY 0
#define STACK_CHECK_VALUE 0xa5                /* default stack value. */
// The following are bits in tFlags.
#define OS_BLOCKABLE  1

typedef unsigned int MEM;
typedef MEM STAK;
typedef MEM FAR* STAKP;


/* 
ITask
Description:
   Parent Class: TaskHdr.
   The ITask class is the parent class of the Task class. The only 
   difference is that the constructors and destructors of the 2 
   classes are different.
   The user should not create instance of ITask. Use Task.
   Only one object should be of Class ITask, and this is the 
   OpSys::idle task. All other tasks should be of class Task.
   All the public elements of ITask are also public to Task.
   Each element of type ITask is an independent cpu process, with 
   its own stack and time slices to operate.
   ITasks are all kept in a linked list, with the head node in 
   OpSys::mainTask.
Data:
   semaphore, bitFlag, MailBox
		       These objects exist in the same memory 
		       space as a C++ union. They contain data 
		       specifically for use by the Semaphore, 
		       BitFlag, or MailBox classes when an object 
		       of class ITask is Blocked by an object of 
		       one of these types.
   blockReturn         When ITask object becomes active after 
		       being blocked by object 'a' of class block, 
		       value from 'a' is stored here (timeout, 
		       done, etc).
   timeOut             Timeout value when waiting on object of 
		       class block. (semaphores, bitflags, etc).
   startOfStack        This is the starting point of the stack. 
		       StackPtr is reset to this each start() 
		       call.
   stackPtr            Store stack pointer here when task is 
		       removed from execution.
   stackLen            Length of stack for this task.
   stack               Pointer to bottom of stack.
   tFlags              Bit flags about this task. Bits include
		       UNBLOCKABLE. This task can not be removed 
		       from active list (if set).
   priority            Priority of this task. from 0 to 255. 
		       Highest priority is largest number. Highest 
		       priority unblocked tasks execute first.
   blockedList             This object is used to put task into linked
					   list of blocked tasks.
   activeList              List of all active tasks.
   tasks                           List of all created tasks.
   timeList                        List of all tasks that are waiting on a timeout.
Methods:
   ITask::ITask        ITask constructor.
   ITask::activate     Put ITask onto active task list.
   ITask::run          Start execution of task at this routine. 
		       That is, Task::run() will be called as an 
		       independent thread of execution, with its 
		       own stack and cpu time slices.
   ITask::doTimeout    Put ITask onto timeout linked list ordered 
		       by the timeout value (longest last).
   ITask::doSetPriority    Internal routine to set/change priority 
		       of ITask. Users should use setPriority().
   ITask::info         Print information about this ITask to the 
		       debug output pipe.
   ITask::start        Start task.
   ITask::stop         Stop task.
   ITask::sleep        Stop task for some number of clock ticks, 
		       then restart.
   ITask::stackFree    Return # of bytes unused in stack. Debug 
		       only.
   ITask::setPriority  Set/change priority of task. Task can be 
		       running or stopped.
   ITask::isBlockable  Return true if task is blockable, false 
		       otherwise.
   ITask::blockable    Make task blockAble (see tFlags).
   ITask::unBlockable  Make task unBlockable (see tFlags).
*/

class ITask;

/*
 class TaskList:
 Description: This class implements a double linked list of task
 Data:
  next,last pointers to next and last elements of list.
  task pointer to task object that this element of the list represents.
 Methods:
*/
class TaskList
{
 protected:
 public:
  TaskList* next;
  TaskList* last;
  ITask* task;

  ObjType objType;
  TaskList(ITask*);
  ~TaskList();

  void link(TaskList*);
  void unlink();
};

class ITask : public Base
{
 public:
  friend class Block;
  friend class Semaphore;
  friend class MailBox;
  friend class BitFlag;
  friend void startTask1();
  friend class Test;
  friend class OpSys;
  virtual void run();
  
 private:
 protected:
  TaskList blockedList;
  TaskList activeList;
  TaskList taskList;
  TaskList timeList;
  
  STAKP startOfStack;
  STAKP stackPtr;
  const unsigned int stackLen;
  STAKP stack;
  short priority;
  short tFlags;
  Block* blocker;
  union {
	  struct {
		   int signals;
		 } semaphore;
	  struct {
		   short type;
		   unsigned long bits;
		 } bitFlag;
	  struct {
		   long response;
		 } mailbox;
	};
  OSRet blockReturn;
  OSTime timeOut;
  void activate();
  void doSetPriority(short priority);
  void doTimeout(OSTime timeout);
 public:
  ObjType objType;
  const char* name;
  
  ITask(STAKP stack, unsigned int stackLen, const char* name);
  void blockable();
  Bool isBlockable();
  void setPriority(short priority);
  void sleep(OSTime timeout);
  int stackFree(int maxCheck);
  OSRet start();
  void stop();
  void unBlockable();

#ifndef NDEBUG
  virtual void info();
#endif
};

 /*
Task
Description:
	Parent Class: ITask.
	Class Task is identical to class ITask, except its constructor
	automatically links the task onto the global task queue, and
	its destructor removes it. Class Task inherits all the ITask
	methods and data.
Methods:
	available.
Usage:

	#include <Task.h>

	#define TASK_STACK_LENGTH ???
	#define TASK_PRIORITY (1..255) ???

	STAK stack[TASK_STACK_LENGTH];

	extern STAKP stack[TASK_STACK_LENGTH]

	Task task(stack, sizeof(stack), TASK_PRIORITY,"Task Name");

*/
class Task : public ITask
{
 private:
 protected:
 public:
  Task(STAKP stack, unsigned int stackLen, short priority,
		 const char* name = 0);
  ~Task();

#ifndef NDEBUG
  virtual void info();
#endif
};


/*
STask
Description:
	Parent Class: Task.
	Class STask is identical to class Task, except it automatically
	allocates its stack from the original program startup stack.
	These tasks are very useful for calling base operating system
	calls when running under operating systems such as dos.
	Class STask inherits all the Task methods and data.
Methods:
	Stask::allocStack   Allocate stack segment. Return -1 if no
				 stack segments available.
Usage:

	#include <Task.h>
	#define TASK_STACK_LENGTH ???
	#define TASK_PRIORITY (1..255) ???

	extern STAKP stack[TASK_STACK_LENGTH]

	STask task(TASK_STACK_LENGTH, TASK_PRIORITY,"Task Name");

*/

class STask : public Task
{
 private:
  STAKP allocStack(unsigned int);
 protected:
 public:
  STask(unsigned int stackLen, short priority, const char* name = 0);
  ~STask();
};

/*
TaskList::link(TaskList* nextObj)
Description:
*/
inline void TaskList::link(TaskList* nextObj)
{
  next = nextObj;
  last = nextObj->last;
  nextObj->last->next = this;
  nextObj->last = this;
}

/*
void TaskList::unlink()
*/

inline void TaskList::unlink()
{
  next->last = last;
  last->next = next;
  next = this;
  last = this;
}


/*
ITask::isBlockable
Description:
	Class ITask.
	Return true if task is blockable.
*/
inline Bool ITask::isBlockable()
{
  return ((tFlags & OS_BLOCKABLE) ? OSTrue:OSFalse);
}

/*
ITask::blockable
Description:
	Class ITask.
	Make task blockable. This is the default state of a task. When
	a task is blockable it can be removed from the active task
	queue.
*/
inline void ITask::blockable()
{
  tFlags |= OS_BLOCKABLE;
}

extern void startTask1();

#endif
