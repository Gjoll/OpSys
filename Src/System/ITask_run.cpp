/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:06  $
  $Workfile:   task3.cpp  $
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
ITask::run
Description:
   Class ITask.
   This is the method that is called when a task is started. Run 
   will be called and executed as an independent task with its own 
   stack and cpu time frames. If ITask::run returns, this task 
   will be halted.
   This shall be overloaded with the run method of the user class 
   derived from Task. ITask::run is virtual.
*/

void ITask::run()
{
  checkInit();
}

