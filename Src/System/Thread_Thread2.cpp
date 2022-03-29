/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:16  $
  $Workfile:   thread2.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <Thread.h>
 
 
/* 
Thread::Thread2
Description:
   Class Thread.
   Thread constructor.
   This initializes the Task parent class, and then calls the 
   ITask::start method. This will cause Thread::run to be started 
   as a separate task. Thread::run will then call the function 
   *iTPtr passed to the constructor.
Parameters:
   t                   The address of the function to execute as a 
                       thread.
   s                   Stack for this thread to use.
   l                   Length of stack passed.
   p                   Thread priority. In range 0..255 with 
                       larger numbers = higher priority.
   name                Optional name for the thread. This is for 
                       debugging only.
*/

Thread::Thread(TPtr1 iTPtr, unsigned int iStackLen,
		short iPriority, const char* name) :
	STask(iStackLen, iPriority, name),
	data(0), tPtr((TPtr) iTPtr)
{
  objType = ThreadType;
  start();
}

