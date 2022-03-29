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
  $Workfile:   task8.cpp  $
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
ITask::doSetPriority
Description:
   Class ITask.
   This routine should never be called by the user. Use
   setPriority instead!
   Set priority of task to passed value, and link task into
   correct place in task linked list. Tasks are ordered by
   priority, highest (largest) priority first, lowest (smallest) 
   last.
Parameters:
   pri                 is the priority to set the task to.
*/

/*
1.	lock out interrupts. Any interrupts that occur while lists 
	are being modified could cause problems.
2.	Set priority variable to passed value.
3.	Unlink from TASKS list if not already. Since priority was 
	changed its place on the tasks list will have to change 
	since list is ordered by priority.
4.	Search through TASKS list for task with lower priority then 
	this task.
5.	Place this task immediately before task found in setup # 4.
6.	If task is on ACTIVE list also, then remove from list and 
	replace is on list in new position, ordered by new priority.
7.	Reenable interrupts.
*/

void ITask::doSetPriority(short pri)
{
  os.lock();								// 1
  priority = pri;							// 2
  taskList.unlink();							// 3
  {									// 4
    TaskList* listPtr = os.taskList.next;

    while ((listPtr != &os.taskList) &&
	   (listPtr->task->priority >= priority))
      listPtr = listPtr->next;

    taskList.link(listPtr);						// 5
  }
  if (activeList.next != &activeList)
    {									// 6.
      activeList.unlink();						// 6
      activate();							// 6
    }
  os.unLock();								// 7
}

