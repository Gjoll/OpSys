/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:58  $
  $Workfile:   iobuf11.cpp  $
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
IOBuf::doSetW
Description:
   Class: IOBuf.
   This sets the field width for the next I/O operation. It is 
   called by the setw() IOBuf manipulator. The user should not 
   directly call doSetW().
Parameters:
   IOBuf               is the IOBuf that is to be modified.
   width               is the new width to set in buf.
*/
IOBuf& doSetW(IOBuf& buf, int newWidth)
{
	buf.width = newWidth;
	return buf;
}

