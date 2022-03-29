/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:02  $
  $Workfile:   opsys.cpp  $
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
OpSys::OpSys
Description:
   Class OpSys.
   OpSys constructor.
   Initialize all operating system circular linked lists. When any 
   OpSys object (semaphores, bitflags, etc) are created They are 
   linked into these lists.

   This constructor creates the default stack from the buffer passed in
   the constructor. Do not use this constructor with operating systems
   that require STask/Thread stacks to be located on the original startup
   stack!

Parameters:
   schFlag             optional initial setting to the schedule 
		       flag. This can be used to control when and 
		       how task scheduling occurs.
*/
/*
1.      Initialize block list.
2.      Initialize but do not start idle task. This really is the currently 
	executing thread.
3.      Set INITIALIZING status, so that no task switched occur.
4.      Set current task to the currently running task (idle).
5.      Initialize stack allocation buffer for Task stacks. This is 
	initialized to the an area in the upper/unused stack area.
6.      Lock out interrupts.
7.      Call operating specific startup routine.
8.      Allow interrupts.
9.      Set priority of idle task to lower priority than is allowed for 
	any normal task.
10.     Put idle task onto active task list.
	scheduling occurs.
*/

OpSys::OpSys(MEM* defStak, int defLen, short iSchFlag) :
	blocks(OS_PRIORITY, "OpSys::BlockList"),
	taskList(&idle),                                                // 1
	activeList(&idle),						// 1
	timeList(&idle),						// 1
	blockedList(&idle),						// 1
	idle(0, 0, "OpSys::Idle"),					// 2
	schFlag(iSchFlag | INITIALIZING),				// 3
	currentTask(&idle)						// 4
#ifndef NOSTACK
	, stackAlloc(defStak, defLen)
#endif
{
  lock();								// 6
  startup();								// 7
  currentTask = &idle;
  unLock();								// 8
  exitFlag = OSFalse;
  idle.doSetPriority(-1);						// 9
  idle.activeList.link(&activeList);					// 10
}


