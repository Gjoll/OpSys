/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:52  $
  $Workfile:   semap.cpp  $
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
Semaphore::Semaphore
Description:
   Class Semaphore.
   Semaphore constructor. Put semaphore onto BLOCK linked list, 
   and initialize all other circular lists to empty. Set name and 
   initial value of semaphore.
Parameters:
   signals             is the initial value to set the semaphore 
                       to. The default is 1.
   flags               is a series of bits that control the action 
                       of this semaphore. The meaning of the flags 
                       are as follow.
                       OS_FIFO - semaphore is a fifo semaphore. 
                       Tasks that are blocked on this semaphore 
                       will become unblocked in FIFO order.
                       OS_PRIORITY - semaphore is a priority 
                       semaphore. Highest priority tasks that are 
                       blocked on this semaphore will become 
                       unblocked before lower priority tasks.
                       If both OS_FIFO and OS_PRIORITY are set, 
                       the semaphore will be a fifo semaphore.
                       The default value for flags is OS_FIFO.
   name                is an optional name to give the semaphore, 
                       used for debugging purposes only.
*/

Semaphore::Semaphore(int iSignals, BFlags bFlags, const char* iName) :
	Block(bFlags, iName == 0 ? "Semaphore" : iName)
{
  objType = SemaphoreType;
  signals = iSignals;
}


/* 
Semaphore::~Semaphore
Description:
   Class Semaphore.
   Semaphore destructor.
*/

Semaphore::~Semaphore()
{
}

