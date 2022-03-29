/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:12  $
  $Workfile:   opsys2.cpp  $
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
OpSys::mainTask
Description:
   Class OpSys.
   This is the idle task. It is called directly from main().
   After it is called, all static/global objects have been 
   constructed. It puts argv into main::argv and argc into 
   main::argc and then allows task switching to occur. This is 
   very important: No task switching is allowed until all the 
   static objects have been constructed!
   Main does some operating system checking to verify that things 
   have not been corrupted, and continues until exitFlag is True.
   When OpSys::exit is called, exitFlag is True, and the priority 
   of the idle task is raised to the maximum. This will cause the 
   idle task to    execute, and detect that the exitFlag is True, 
   and will cause mainTask() to return to main. Main will then 
   return to the base operating system.
Parameters:
   argv                this is a copy of argv as passed to main.
   arg                 this is a copy of argc as passed to main.
*/

int OpSys::mainTask(int iArgc, char** iArgv)
{
	os.argv = iArgv;				// store global argv and argc
	os.argc = iArgc;				// pointers.
	os.schFlag &= ~INITIALIZING;	// allow task scheduling.
	os.idle.unBlockable();			// Cant block idle task.
	while (os.exitFlag == OSFalse)
	{								// loop until os.exit() called
		schedule();					// run any scheduled tasks
#ifndef NDEBUG
		//check();					// ... do something usefull
#endif
	}
	return(os.exitValue);			// return exit value.
}

