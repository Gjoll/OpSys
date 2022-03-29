/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:22  $
  $Workfile:   iobuf4a.cpp  $
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
IOBuf::fail
Description:
   Class: IOBuf.
   Get failure status of IOBuf I/O operations. Returns True if the 
   last operation failed, False if it succeeded.
*/

Bool IOBuf::fail()
{
	return(((successFlag == OSTrue) ? OSFalse : OSTrue));
}

