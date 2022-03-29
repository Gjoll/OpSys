/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:06  $
  $Workfile:   iobuf28.cpp  $
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
IOBuf::operator>>5
Description:
   Class: IOBuf.
   Read a single character from the IOBuf and return it. If 
   IOBuf::skip has been set, so that white space is to be ignored, 
   all non printing data and spaces will be thrown away.
Bugs:
   This routine assumes that ASCII is used. If character set is 
   not ASCII and IOBuf::skip is on, then the results will probably 
   not be correct.
*/

IOBuf& IOBuf::operator>>(char& c)
{
	do {
		successFlag = get(&c);
	} while (
		(successFlag == OSTrue) &&
		(skipWhiteSpace == OSTrue) &&
		((c <= ' ') || (c > '|'))
		);
	return(*this);
}


