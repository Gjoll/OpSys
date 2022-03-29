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
  $Workfile:   iostr3.cpp  $
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
IOString::doFlush
Description:
   Class: IOString.
   doFlush() is called by the flush manipulator. It clears all 
   data from the IOString. Any attempts to read data will fail 
   until data is written to the IOString.
*/
Bool IOString::doFlush()
{
	front = back = 0;
	buffer[0] = '\0';
	return OSTrue;
}

