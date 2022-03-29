/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/

/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:56  $
  $Workfile:   break.h  $
*/

#include <osConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <bitFlag.h>
#include <Thread.h>

/* 
USBreak
Description:
   USBreak implements a ctl-c interrupt handler, that when 
   triggered by DOS reading a ctl-c, will halt the current 
   program, calling the os.exit() function, and executing all 
   global destructors.
*/

class USBreak
{
private:
	static unsigned oldSeg;
	static unsigned oldOff;
	static unsigned short breaks;
private:
public:
	USBreak();
	~USBreak();
};


 

