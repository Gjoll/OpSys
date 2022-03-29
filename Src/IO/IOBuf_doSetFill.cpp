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
  $Workfile:   iobuf12.cpp  $
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
IOBuf::doSetFill
Description:
   Class: IOBuf.
   This method is called by the IOBuf setfill manipulator. It 
   should not be called directly by the user. It sets the fill 
   character of the IOBuf to the passed value.
Parameters:
   IOBuf               is the buffer to modify the fill parameter 
                       to.
   fill                is the new fill character to set in buf.
*/
IOBuf& doSetFill(IOBuf& buf, char newFill)
{
	buf.fill = newFill;
	return buf;
}

