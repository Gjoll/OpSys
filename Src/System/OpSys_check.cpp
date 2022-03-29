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
  $Workfile:   opsys1.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <debug.h>

/* 
OpSys::check
Description:
   Class OpSys.
   Check integrity of all OpSys double linked lists, and check for 
   stack overflow in any task/thread objects.
   If an error is detected, an appropriate error message is 
   written to the debug object.
   This function is used mainly as a debugging function.
*/

void OpSys::checkTask(ITask* tPtr)
{
  ITask* t1Ptr;

  lock();
  t1Ptr = tPtr->taskList.next->last->task;
  unLock();
  assert(t1Ptr == tPtr);

  lock();
  t1Ptr = tPtr->activeList.next->last->task;
  unLock();
  assert(t1Ptr == tPtr);

  lock();
  t1Ptr = tPtr->blockedList.next->last->task;
  unLock();
  assert(t1Ptr == tPtr);

  lock();
  t1Ptr = tPtr->timeList.next->last->task;
  unLock();
  assert(t1Ptr == tPtr);

  lock();
  t1Ptr = tPtr->taskList.last->next->task;
  unLock();
  assert(t1Ptr == tPtr);

  lock();
  t1Ptr = tPtr->activeList.last->next->task;
  unLock();
  assert(t1Ptr == tPtr);

  lock();
  t1Ptr = tPtr->blockedList.last->next->task;
  unLock();
  assert(t1Ptr == tPtr);

  lock();
  t1Ptr = tPtr->timeList.last->next->task;
  unLock();
  assert(t1Ptr == tPtr);
}

void OpSys::checkBlocks()
{
	TaskList* listPtr;
	Block* bPtr = os.blocks.nextBlocks;
   TaskList* taskList, *taskPtr;

	do
  	{
   	Block* b1Ptr;

    	lock();
    	b1Ptr = bPtr->nextBlocks->lastBlocks;
    	unLock();
    	assert(b1Ptr == bPtr);

    	lock();
    	b1Ptr = bPtr->lastBlocks->nextBlocks;
    	unLock();
    	assert(b1Ptr == bPtr);

		lock();
		taskList = &bPtr->blockedList;
		taskPtr = bPtr->blockedList.next->last;
		unLock();
		assert(taskPtr == taskList);

    	lock();
    	taskPtr = bPtr->blockedList.last->next;
    	unLock();
		assert(taskPtr == taskList);

		do
		{
			listPtr = bPtr->blockedList.next;
			/*
	   	Note: Tasks can be removed from blocked list
	   	in the middle of check!
	   	*/
			while (listPtr != &bPtr->blockedList)
			{
	   		ITask* tPtr = listPtr->task;
	   		if (listPtr->next == listPtr)
	   			break;
	    		else
	      		checkTask(tPtr);
	    		listPtr = listPtr->next;
	  		}
   	} while (listPtr != &bPtr->blockedList);
		bPtr = bPtr->nextBlocks;
	} while (bPtr != &os.blocks) ;
}

void OpSys::checkTasks()
{
	TaskList* listPtr = os.taskList.next;

	do
   {
      ITask* tPtr = listPtr->task;
      checkTask(tPtr);
#ifdef CHECKSTACK
      short freeBytes;
   	if ((tPtr->stackLen != 0) &&
	  		((freeBytes = tPtr->stackFree(MIN_STACK)) < MIN_STACK))
		{
	  		(*Debug::current) << "\nStack Overflow !. Task["
	    							<< tPtr->name
	      						<< "] "
									<< freeBytes
		  							<< "\n";
	  		exit(1);
		}
#endif
		listPtr = listPtr->next;
	} while (listPtr != &os.taskList) ;
}

void OpSys::check()
{
	checkBlocks();
	checkTasks();
}

