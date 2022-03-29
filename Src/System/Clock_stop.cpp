/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:46  $
  $Workfile:   clock2.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <OsTypes.h>
#include <clock.h>

/* 
Clock::stop
Description:
   Class Clock.
   Stop clock operation. If clock is currently not running, do not 
   stop again.
*/

void Clock::stop()
{
  if (started == OSTrue)
    {
      doStop();
      started = OSFalse;
    }
}

