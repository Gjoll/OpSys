/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:20  $
  $Workfile:   opsys9.cpp  $
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
OpSys::lock
Description:
   Class OpSys.
   Disable any interrupts that will call OpSys objects. lock is 
   called when OpSys is modifying pointers in such a way that the 
   system is unusable until the operation is complete.
   The routine disInts() is called to perform the disabling.
   It is an error to call OpSys::lock() twice in a row w/o an 
   intervening OpSys::unLock. It is also an error to call 
   OpSys::unLock w/o previously calling OpSys::lock().
   This routine should not be called by the user!
*/

void OpSys::lock()
{
  disInts();
  assert(!(os.schFlag & LOCKED));	// verify os.lock() not called prior.
  os.schFlag |= LOCKED;
};


/* 
OpSys::unLock
Description:
   Enable any interrupts disabled by lock(). The assemble enInts() 
   is called to perform the enabling.
   It is an error to call lock() twice in a row w/o an intervening 
   unLock(). It is also an error to call unLock() w/o previously 
   calling lock().
   The clock ticks that occur between a lock() and unLock() call
   are counted in the variable OpSys::ticks. When unLock() is called,
   execute these many OpSys::clockTick() calls.
*/

void OpSys::unLock()
{
  short lTicks = os.ticks;
  os.ticks = 0;
  assert(os.schFlag & LOCKED);	// verify os.lock() called prior.
  os.schFlag &= ~LOCKED;
  enInts();
  while (lTicks > 0)
    {
      clockTick();
      lTicks -= 1;
    }
};

