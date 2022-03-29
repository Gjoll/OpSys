/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:36  $
  $Workfile:   iostr4.cpp  $
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
IOString::putBack
Description:
   Class: IOString.
   Put one character onto the FRONT of IOString. Returns True if  
   put worked, or False if no room in the IOString for another 
   character.
   Access to the IOString is limited to one task at a time by the 
   access semaphore. Multiple tasks attempting to access the 
   IOString object will be blocked, and only one task at a time 
   will be allowed access.
Parameters:
   c                   is the character to put.
*/

Bool IOString::putBack(char c)
{
	Bool success = OSFalse;
	access.wait();
	if (back > 0) {
		buffer[--back] = c;
		success = OSTrue;
	}
	access.signal();
	return(success);
}

