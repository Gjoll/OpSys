/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:24  $
  $Workfile:   iobuf4c.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <IoBuf.h>
extern IOBuf& doSkip(IOBuf&, Bool);
/* 
IOBuf::skip
Description:
   Class: IOBuf.
   Set skip white space on or off. If on, white space will be 
   thrown away on reads.
Parameters::
   flag                is either True (skip on) or False (skip 
                       off).
*/

IOMANIPBOOL skip(Bool flag)
{
	return(IOMANIPBOOL(doSkip, flag));
}

