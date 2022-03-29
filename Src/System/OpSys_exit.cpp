/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:16  $
  $Workfile:   opsys6.cpp  $
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
OpSys::exit
Description:
   Class OpSys.
   OpSys::exit is called when the program is to be aborted, but 
   the current task can not be blocked. If the system should exit 
   immediately then OpSys::exit() should be called.
   The exit flag, which the idle task monitors, is set, and the 
   idle task is set to a higher priority than any other task.
   At the next task switch, this idle task will start, the exit 
   flag will be read, and the program will exit.
   Value will be returned to the base operating system as the exit 
   value when this program quits.
   If the program is a stand alone program, this will never be 
   called.
Parameters:
   value               is the value to return to base operating 
                       system.
*/

void OpSys::exit(int value)
{
  exitLater(value);
  schedule();
}

