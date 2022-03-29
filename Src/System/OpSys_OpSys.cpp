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
OpSys::~OpSys
Description:
   OpSys destructor. Unlink all objects linked into OpSys lists. 
   This is not really necessary, as the system can stop with these 
   links in place or deleted, but is done for completeness.
Implementation:
   1.  Stop task swaps from occurring.
   2.  lock out interrupts.
   3.  Call operating specific shutdown routine.
   4.  Iterate on every object of class Block in the system.
   5.  Remove all tasks that are on the blocker objects blocked 
      task list
   6.  Remove blocker object from Block list.
   7.  Remove all tasks from the active task list.
   8.  remove all tasks from the created task list.
   9.  Remove all tasks that are on the task timeout list.
*/

OpSys::~OpSys()
{
  schFlag |= INITIALIZING;						//1
  lock();								//2
  shutdown();								//3
  while (blocks.nextBlocks != &blocks)					//4
    {
      ((Block*) blocks.nextBlocks)->doUnBlockAll();			//5
      Block* next =(Block*) blocks.nextBlocks;
      next->unlinkBlocks();						//6
    }
  while (activeList.next != &activeList)				//7
    {
      TaskList* next = activeList.next;
      next->unlink();
    }
  while (taskList.next != &taskList)					//8
    {
      TaskList* next = taskList.next;
      next->unlink();
    }
  while (timeList.next != &timeList)					//9
    {
      TaskList* next = timeList.next;
      next->unlink();
    }
  unLock();
}


/* 
main
Description:
   Note that main() is not declared by the user!
   Main is the entry point to the system. It initializes all 
   static/global objects and then calls mainTask(). When/if 
   mainTask() returns, exitOpSys() is called. exitOpSys() is an 
   function defined in OsConfig.h that usually calls the "C" 
   function exit(). In a stand along application exitOpSys() is 
   usually a blank function. It is usually an error for a stand 
   alone system to ever return.
*/

main(int argc, char** argv)
{
	short done = 0;
	int exitValue = 0;
	while (done == 0)
	{
	  exitValue = os.mainTask(argc, argv);
	  exitOpSys(exitValue);
	}
	return exitValue;
}

