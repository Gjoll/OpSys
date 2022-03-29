/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:08  $
  $Workfile:   iobuf32.cpp  $
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
IOBuf::operator<<12
Description:
   Class: IOBuf.
   Write a character string to the IOBuf. If IOBuf::setw has been 
   called, then the written string is padded out to the length 
   specified, by adding fill chars onto the end of the string. The 
   fill char is set by the fill manipulator. The field width is 
   reset to 0 after this call. */
IOBuf& IOBuf::operator<<(register const char* str)
{
	short count = 0;
	successFlag = OSTrue;
	while ((*str != '\0') && (successFlag == OSTrue)) {
		successFlag = put(*str++);
		count += 1;
	}
	while ((count < width) && (successFlag == OSTrue)) {
		successFlag = put(fill);
		count += 1;
	}
	width = 0;
	return(*this);
}

