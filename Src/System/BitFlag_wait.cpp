/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:36  $
  $Workfile:   bitflag2.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <BitFlag.h>

/* 
BitFlag::wait
Description:
   Class BitFlag.
   Block current task until the indicated bits are set in the 
   bitflag. The task can wait until all bits set in waitBits have 
   been set in BitFlag::bits, or only until one or more of the 
   bits in waitBits has also been set in BitFlag::bits. (See 
   OSWaitBits).
   An optional timeout can specify the maximum number of clock 
   ticks the task should remain blocked.
   The following are the possible return values from 
   BitFlag::wait() and their meanings.
   OS_DONE             The specified bits in BitFlag::bits have 
                       been set.
   OS_TIMEOUT          The timeout period expired without the 
                       specified bits in BitFlag::bit being set.
   OS_BLOCKERR         The calling task is not blockable, and can 
                       not be removed from the active task queue.
   OS_DELETED          The BitFlag object that the task was 
                       waiting for was deleted.
Parameters:
   b                   are the bits that the task is waiting to be 
                       set.
   t                   specifies whether to wait for one or more 
                       of the bits in b to be set, or for all.
   o                       is an optional timeout. Default is 
                       forever.
*/

/*
1.	Check that BitFlag.has been initialized.
2.	lock out interrupts.
3.	If tasks wait condition is currently satisfied by the current 
	state of the BitFlag bits then return immediately with DONE.
4.	put task onto BitFlags waiting list.
5.	Store conditions of wait for BitFlag::signal() to later evaluate 
	as the state of the BitFlag changes.
6.	If timeout specified, put task onto timeout list.
7.	Block task.
8.	Enable interrupts.
9.	Return completion status.
*/
OSRet BitFlag::wait(unsigned long wbits, OSWaitBits type, OSTime timeout)
{
  OSRet retVal;
  checkInit();								//1
  os.lock();								//2
  if (									//3
      ((bits & wbits) == wbits) ||
      (((bits & wbits) != 0) && (type == OS_ONE))
      ) {
    retVal = OS_DONE;
  } else {								//4
    register Task* tPtr = (Task*) os.currentTask;
    tPtr->bitFlag.type = type;						//5
    tPtr->bitFlag.bits = wbits;						//6
    retVal = blockTask(timeout);					//7
  }
  os.unLock();								//8
  return(retVal);							//9
}

