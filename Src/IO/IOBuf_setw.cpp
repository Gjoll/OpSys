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
  $Workfile:   iobuf4b.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <IoBuf.h>
extern IOBuf& doSetW(IOBuf&, int);
/* 
IOBuf::setw
Description:
   Class: IOBuf.
   Set the minimum field width for the next I/O operation. After 
   the next I/O operation that uses the field width, the field 
   width is reset to 0.
Parameters::
   width               is the field width to use for the next 
                       output operation.
*/

IOMANIPINT setw(int width)
{
	return(IOMANIPINT(doSetW, width));
}

