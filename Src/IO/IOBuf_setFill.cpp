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
  $Workfile:   iobuf4d.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <IoBuf.h>
extern IOBuf& doSetFill(IOBuf&, int);
/* 
IOBuf::setFill
Description:
   Class: IOBuf.
   Set fill character. This character is used to pad out strings 
   to the minimum field width specified by the setw() manipulator.
Parameters::
   fill                is the new fill character.
*/

IOMANIPINT setFill(int fill)
{
	return(IOMANIPINT(doSetW, fill));
}

