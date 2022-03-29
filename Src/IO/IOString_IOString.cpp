/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:32  $
  $Workfile:   iostr.cpp  $
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
IOString::IOString
Description:
   Class: IOString.
   IOString constructor.
   This initializes the pointers to the external memory and 
   length, and sets up the access semaphore.
Parameters:
   iBuffer             This is the memory used to store the string 
                       data. It is a character buffer defined by 
                       the user external to the IOString. It 
                       should not be used for any other purpose, 
                       nor should it be deleted before this 
                       IOString object is deleted.
   iLength             Number of characters of data in iBuffer.
*/

IOString::IOString(char* iBuffer, short iLength) :
	access(1, OS_PRIORITY, "IOBuf::access"), IOBuf()
{
	buffer = iBuffer;
	length = iLength;
	doFlush();
}

