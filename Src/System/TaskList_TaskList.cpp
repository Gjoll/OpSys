/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:40  $
  $Workfile:   ptrblk.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <Task.h>

/* 
TaskList::TaskList
Description:
	Class ITask::Taskist.
	This is the ITask::TaskList constructor. Initialize all circular
	linked lists to empty
Parameters:
*/

TaskList::TaskList(ITask* iTask)
{
  objType= PtrBlockType;
  next = this;
  last = this;
  task = iTask;
}


/*
TaskList::~TaskList
Description:
	Class ITask::TaskList.
	TaskBlockHdr destructor.
*/

TaskList::~TaskList()
{
#ifndef NDEBUG
  assert(next == this);
  assert(last == this);
  unlink();
#endif
}
