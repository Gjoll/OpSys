/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.
*/
/*                                                     
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:18  $
  $Workfile:   OpSys.h  $
*/

#ifndef OPSYS_H
#define OPSYS_H
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <OsTypes.h>

#ifndef NOSTACK
#include <MemAlloc.h>
#endif

// schFlag bits
// Each of the following is a bit in schFlag.
#define NO_OPTIONS      0       /* No options set.*/
#define NOSCHEDSWAP     1       /* schedule() will not swap tasks.*/
#define NOTIMERSWAP     2       /* clockTick() will not cause task*/
				/* switch. This is only set/cleared by*/
				/* objects of class Clock, during*/
				/* their construction.*/
#define INITIALIZING    4       /* system is initializing. Task */
				/* swapping not allowed. */
#define LOCKED          8       /* interrupts are curently locked */
				/* by a call to OpSys::lock(). */
				/* locks are cleared by OpSys::unLock() */
// Assembly routines.
// The following routines are instantiated in config.asm. They
// are used for task swapping and interrupt control.
extern "C" {
	void FAR swap(STAKP FAR* oldSp, STAKP newSp);
	void FAR startTask(STAKP FAR* oldSp, STAKP newSp);
	void enInts();
	void disInts();
}
/* 
OpSys
Description:
   Parent Class: Base.
   Class OpSys is the operating system base class. All the data 
   and methods to enable task scheduling and task swapping are in 
   this class.
   There is only ONE object of type OpSys allowed. It MUST be 
   defined as follows.
   a. It must be named "os".
   b. It must be defined before any other objects that make any 
      use of the operating system, such as tasks, semaphores,
      bitflags, etc. The constructor for OpSys::os MUST be 
      executed before the constructor for any objects of the above 
      classes. See section 1.1.
   c. It must be global.
Usage:
   #include <OpSys.h>
   OpSys os;
Data:
   int argc            set to argc as passed to main().
   char** argv         set to argc as passed to main().
   ITask* currentTask  Pointer to currently executing task.
   Bool exitFlag       Set if os.exit() has been called.
   int exitValue       Exit value when os.exit() called.
   ITask idle          Idle task. This task will run when no other 
		       task is runnable. If any other task is 
		       runnable it will run first. The idleTask is 
		       not blockable.
   short schCount      Counts # of swap()'s vs. noSwaps()'s 
		       performed. If more noSwap()'s than 
		       swap()'s, swapping is not allowed and
		       schFlag is set to nonzero.
   short schFlag       Controls scheduling. If not 0, then task 
		       switching is not enabled.
   tasks               is the task linked list head node. All 
		       tasks/threads are linked onto this circular 
		       list.
   OSTime tickCount    Current count of clock ticks.
   short ticks         Count of clock ticks that have occurred 
		       since last OpSys::lock() call. 
		       OpSys::unLock will call OpSys::clockTick() 
		       this many times when interrupts and clock 
		       ticks are unlocked.
   MemAlc stackAlloc   Stacks are allocated from this memory 
		       region. The size of stackAlloc is set by 
		       the second parameter to the OpSys object, 
		       which defines the number of kilo long words 
		       allocated to stacks.
Methods:
   OpSys::OpSys        Constructor.
   OpSys::~OpSys       Destructor.
   OpSys::blockInfo    Print out all information about all objects 
		       derived from class Block.
   OpSys::check        debug task. Check integrity of links.
   OpSys::clockTick    Called by the clock interrupt task to 
		       signal another clock interrupt, and unblock 
		       any tasks whose timeouts have expired.
   OpSys::doSchedule   Initiate task swap if higher priority task 
		       waiting to be executed.
   OpSys::elapsedTime  Check elapsed time between event time1 and 
		       time2, or between event time and current 
		       time.
   OpSys::exit         Stop OpSys and return control to base os 
		       (unix, dos, etc).
   OpSys::exitLater    Same as exit, but do later.
   OpSys::getCurrentTask   Return pointer to currently executing 
		       task.
   OpSys::lock         Disable all interrupts that may call 
								any OpSys methods. Used for OpSys critical regions.
	OpSys::locked   Return True if lock() has been called w/o unLock().
   OpSys::mainTask     Idle task executes mainTask().
   OpSys::now          Return current clock tick count.
   OpSys::schedule     Initiate task swap if higher priority task
		       waiting to be executed. This locks out
		       interrupts, calls OpSys::doSchedule, and 
		       reenables interrupts.
   OpSys::shutdown     Operating specific routine called at system 
		       shutdown.
   OpSys::startup      Operating specific routine called at system 
		       startup.
   OpSys::swapOff      Do not allow scheduler to initiate 
		       rescheduling.
   OpSys::swapOn       Allow scheduler to initiate rescheduling.
   OpSys::taskInfo     Print out info on all tasks, itasks, or 
		       threads.
   OpSys::timerSwapOn  Allow clockTick() to initiate rescheduling.
   OpSys::timerSwapOff Do not allow clockTick() to initiate 
		       rescheduling
   OpSys::unLock       Enable interrupts disabled by lock.
*/

class OpSys : public Base
{
  friend class OpSys;
  friend class Clock;
  friend class Block;
  friend class ITask;
  friend void startTask1();
  friend class Test;
  friend class BitFlag;
  friend class Semaphore;
  friend class MailBox;
  friend class Task;
  friend class STask;
 private:
  Block blocks;
  VOLATILE Bool exitFlag;
  int exitValue;
  short schCount;
  short schFlag;
  OSTime tickCount;
  short ticks;

  TaskList blockedList;
  TaskList activeList;
  TaskList taskList;
  TaskList timeList;

  ITask idle;                     // must be initialized AFTER tasks!
    ITask* currentTask;

#ifndef NOSTACK
  MemAlloc stackAlloc;
#endif

  static void checkBlocks();
  static void checkTask(ITask*);
  static void checkTasks();
 public:
  char** argv;
  int argc;
#ifndef NDEBUG
  unsigned int swapCount;
#endif
  OpSys(short kiloStack, short=NO_OPTIONS);
  OpSys(MEM*, int, short=NO_OPTIONS);
  ~OpSys();
  static void blockInfo();
  static void clockTick();
  static void check();
  static void doSchedule();
  static OSTime elapsedTime(OSTime time1, OSTime time2);
  static OSTime elapsedTime(OSTime time);
  static void exit(int);
  static void exitLater(int);
  static Task* getCurrentTask();
  static void lock();
  static Bool locked();
  static int mainTask(int, char**);
  static OSTime now();
  static void schedule();
  static void shutdown();
  static void startup();
  static void swapOff();
  static void swapOn();
  static void taskInfo();
  static void timerSwapOff();
  static void timerSwapOn();
  static void unLock();
} ;

extern OpSys os;
extern STAK** curSp;
extern STAK* newSp;

/*
OpSys::getCurrentTask
Description:
   Class OpSys.
   Return pointer to currently executing task.
*/
inline Task* OpSys::getCurrentTask()
{
  return (Task*) os.currentTask;
};

/*
OpSys::now
Description:
	Class OpSys.
	Return current clock tick count. The clock tick count is
	incremented at each clock interrupt. This serves as a time
	interval counter.
*/
inline OSTime OpSys::now()
{
  return(os.tickCount);
};


/*
OpSys::elapsedTime1
Description:
	Class OpSys.
	Return the number of clock ticks between the passed time
	'time1' and 'time2'. If 'time1' occurred before 'time2' then a
	negative number is returned.
Parameters:
	time1               is the earliest of the 2 times.
	time2               is the later of the 2 times.
*/

inline OSTime OpSys::elapsedTime(OSTime time1, OSTime time2)
{
  return(time2 - time1);
};

/*
OpSys::elapsedTime2
Description:
	Class OpSys.
	Return the number of clock ticks between the passed time 't'
	and the current time. If 't' has already occurred (is in the
	past) then a negative number is returned.
Parameters:
	time              is the time to compare to OpSys::now. time
			  is assumed to be earlier than OpSys::now.
*/

inline OSTime OpSys::elapsedTime(OSTime time)
{
  return(os.now() - time);
};

/*
OpSys::locked
Description:
	Class OpSys.
	Return true if interrupts are currently locked, false
	otherwise.
*/
inline Bool OpSys::locked()
{
  return (os.schFlag & LOCKED) ? OSTrue : OSFalse;
};

/*
OpSys::swapOff
Description:
	Class OpSys.
	Disallow OpSys::schedule from swapping tasks if more
	OpSys::swapOff calls have been made then OpSys::swapOn calls.
	At startup no OpSys::swapOn or OpSys::swapOff calls have been
	made.
	When this is on, no task swaps will be made, so that the
	current task will continue to run indefinitely. A critical
	section of code can be enclosed in OpSys::swapOff and
	OpSys::swapOn calls to insure that no other task will become
	enabled and interrupt the current task.
*/

inline void OpSys::swapOff()
{
  if (os.schCount++ == 0)
    os.schFlag |= NOSCHEDSWAP;
};

/*
OpSys::swapOn
Description:
	Class OpSys.
	Allow OpSys::schedule to swap tasks. If more OpSys::swapOff
	calls have been made then OpSys::swapOn calls, task swapping is
	disabled.
	This call undoes the effect of one OpSys::swapOff call.
	A critical section of code can be enclosed in OpSys::swapOff
	and OpSys::swapOn calls to insure that no other task will
	become enabled and interrupt the current task.
*/

inline void OpSys::swapOn()
{
  if (--os.schCount == 0)
    os.schFlag &= ~NOSCHEDSWAP;
};

/*
OpSys::timerSwapOff
Description:
	Class OpSys.
	Disallows clock interrupt routine from initiating task
	rescheduling if a blocked tasks timeout expires.
	This should only be called from Clock class methods. It is not
	a user routine.
	In this mode when a clock interrupt occurs, and a task timeout
	also occurs, a task switch will not be made to the new
	unblocked task.
	This undoes the effect of one or more previous
	OpSys::timerSwapOn calls.
	This should only be called by the Clock constructor.
*/
inline void OpSys::timerSwapOff()
{
  os.schFlag |= NOTIMERSWAP;
};

/*
OpSys::timerSwapOn
Description:
	Class OpSys.
	Allow clock interrupt routine to initiate task rescheduling if
	a blocked tasks timeout expires.
	In this mode when a clock interrupt occurs, and a task timeout
	also occurs, a task switch may be made to the new unblocked
	task before schedule() returns to the interrupt routine.
	This undoes the effect of one or more previous
	OpSys::timerSwapOff calls.
	This should only be called by the Clock constructor.
*/
inline void OpSys::timerSwapOn()
{
  os.schFlag &= ~NOTIMERSWAP;
};


#endif
