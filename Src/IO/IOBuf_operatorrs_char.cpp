/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:14  $
  $Workfile:   iobuf39.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <IoBuf.h>
/* 
IOBuf::operator<<5
Description:
   Class: IOBuf.
   Write a single character to the IOBuf. The field width is 
   ignored during writing, but is reset to 0 after the write.
*/
IOBuf& IOBuf::operator<<(char c)
{
	successFlag = put(c);
	width = 0;
	return(*this);
}

