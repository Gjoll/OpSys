/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision:   2.1  $
  $Modtime:   01 May 1993 09:34:26  $
  $Workfile:   segv.cpp  $
*/
#include <opsys.h>
#include <ossun.h>
#include <segv.h>
#include <signal.h>
#include <debug.h>
typedef void (*func)();
static short errFlag;
/* 
SegV::intSegv
Description:
   This is the routine called when a segmentation violation signal 
   is received. It prints the current task name and task object 
   address to the debug object, and then exits back to the SUN os.
   This routine must never be called directly by the user!
*/
static void intSegV()
{
	if (errFlag++ != 0)
		exit(0);
	const char* name = os.currentTask->name;
	if (name == 0)
		name = "NoName";
	(*Debug::current) << "Segmentation Violation.\n"
	    << " Current task object address "
	    << hex << (long) os.currentTask
	    << " task name " << name << "\n";
	os.check();
	os.taskInfo();
	os.blockInfo();
	os.exit(-1);
}

/* 
SegV::SegV
Description:
   SegV constructor. Install signal handler to intercept segment 
   violations.
*/
SegV::SegV()
{
	errFlag = 0;
	static sigvec newVec = {&intSegV, SIGSEGV, 0};
	sigvec(SIGSEGV, &newVec, &oldVec);
}

/* 
SegV::~SegV
Description:
   SegV destructor. Remove segmentation violation signal handler.
*/
SegV::~SegV()
{
	sigvec newVec;
	sigvec(SIGSEGV, &oldVec, &newVec);
}
 

