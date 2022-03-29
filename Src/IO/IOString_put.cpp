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
  $Workfile:   iostr1.cpp  $
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
IOString::put
Description:
   Class: IOString.
   Put one character onto the IOString. Returns True of put 
   worked, or False if no room in the IOString for another 
   character.
   This routine is called by the formatted I/O routines of class 
   IOBuf.
   Access to the IOString is limited to one task at a time by the 
   access semaphore. Multiple tasks attempting to access the 
   IOString object will be blocked, and only one task at a time 
   will be allowed access.
Parameters:
   c                   is the character to put.
*/
Bool IOString::put(char c)
{
	Bool success = OSFalse;
	access.wait();
	if (front < length - 1) {
		buffer[front++] = c;
		buffer[front] = '\0';
		success = OSTrue;
	}
	access.signal();
	return(success);
}

