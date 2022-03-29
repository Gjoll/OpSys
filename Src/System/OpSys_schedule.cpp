/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:18  $
  $Workfile:   opsys8.cpp  $
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
#include <Pipe.h>

/* 
OpSys::schedule
Description:
   Class OpSys.
   This routine will perform any rescheduling necessary to start 
   the highest priority task running. If the calling routine is 
   the highest priority task running then no action will be taken.
*/

void OpSys::schedule()
{
  lock();
  doSchedule();
  unLock();
};

