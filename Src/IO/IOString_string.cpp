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
  $Workfile:   iostr6.cpp  $
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
IOString::string
Description:
   Class: IOString.
   Return the address of the next character in the IOString that 
   will be returned via the get() call. This address is the 
   address of a null terminated string of characters. get() calls 
   will increment this address by one. put() calls will add one 
   more character onto the end of this string.
*/

char* IOString::string()
{
	return buffer + back;
};


