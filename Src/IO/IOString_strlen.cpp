/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:38  $
  $Workfile:   iostr5.cpp  $
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
#include <IoBuf.h>
#include <IoString.h>

/* 
IOString::strlen
Description:
   Class: IOString.
   Return the number of characters in the string. get() calls do 
   not affect this count, only put() and flush calls.
*/

short IOString::strlen()
{
	return front;
};


