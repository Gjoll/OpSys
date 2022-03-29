/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:34  $
  $Workfile:   iostr2.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OsTypes.h>
#include <IoBuf.h>
#include <IoString.h>
/* 
IOString::get
Description:
   Class: IOString.
   Get one character from the IOString. If there are no more 
   characters to get, then return false, otherwise return True. 
   This routine is called by the formatted I/O routines in IOBuf.
Parameters:
   c                   is where to store the read character.
*/
Bool IOString::get(char* c)
{
	Bool success = OSFalse;
	access.wait();
	if (back < front)
	{
		*c = buffer[back++];
		success = OSTrue;
	}
	else *c = '\0';
	access.signal();
	return success;
}

