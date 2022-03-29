/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:20  $
  $Workfile:   iobuf47.cpp  $
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
IOBuf::flush
Description:
   Class: IOBuf.
   The flush manipulator calls the virtual function IOBuf::doFlush 
   to clear the IOBuf.
*/

IOBuf& flush(IOBuf& b)
{
	b.doFlush();
	return b;
}

