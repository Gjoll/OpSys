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
  $Workfile:   task1.cpp  $
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
ITask::activate
Description:
   Class ITask.
   Put task 'task' onto active list in correct position after it 
   has been removed for any reason.
   All tasks (active or not) are put on the TASKS list in order of 
   their priority. All active tasks are also put onto the ACTIVE 
   task list in order of their priority. To find the place to put 
   on the active list, search foreword from current task on TASKS 
   list for a task 'a' that is also on ACTIVE list (has been 
   activated. This task 'a' is, by definition, of lesser priority 
   then the this task, because it is after this task on the TASKS 
   list. Insert this task into ACTIVE task list immediately before 
   task 'a'.
*/
void ITask::activate()
{
	if (stack != (STAKP) -1)
    {
		TaskList* listPtr = taskList.next;

		while ((listPtr->task->activeList.next ==
					&listPtr->task->activeList) &&
				(listPtr != &os.taskList))
			listPtr = listPtr->next;
		activeList.link(&listPtr->task->activeList);
	}
	blocker = 0;
}

