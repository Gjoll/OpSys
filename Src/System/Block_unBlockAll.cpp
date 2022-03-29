/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:42  $
  $Workfile:   block2.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <OsTypes.h>

/* 
Block::unBlockAll
Description:
   Class Block.
   Unblock all tasks waiting on this Block object. All tasks will  
   be placed back onto the active task queue, and will be executed 
   when their priority is highest.
*/

/*
1.	Lock out interrupts while modifying the links.
2.	Unblock all tasks.
3.	Enable interrupts.
*/
void Block::unBlockAll() 
{
  os.lock();								// 1
  doUnBlockAll();							// 2
  os.unLock();								// 3
}

