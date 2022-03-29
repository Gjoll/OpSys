/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:00  $
  $Workfile:   iobuf14.cpp  $
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
IOBuf::doSkip
Description:
   Class: IOBuf.
   doSkip is called by the IOBuf manipulator IOBuf::skip. It 
   should not be called by the user. It sets the skipWhiteSpace 
   flag to the passed Boolean value.
Parameters:
   UIBuf               is the IOBuf whose skip flag is being 
                       modified.
   skip                is the value to set skip space flag to in 
                       IOBuf.
*/
IOBuf& doSkip(IOBuf& buf, Bool newSkip)
{
	buf.skipWhiteSpace = newSkip;
	return buf;
}

