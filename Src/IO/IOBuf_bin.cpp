/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:16  $
  $Workfile:   iobuf44.cpp  $
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
IOBuf::bin
Description:
   Class: IOBuf.
   This IOBuf manipulator will set the base of the next number to 
   digit string, or digit string to number conversions to binary. 
   After the next conversion, the base will be reset to decimal.
*/
IOBuf& bin(IOBuf& b)
{
	b.base = 2;
	return b;
}

