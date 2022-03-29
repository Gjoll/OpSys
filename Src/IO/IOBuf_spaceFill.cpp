/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:18  $
  $Workfile:   iobuf46.cpp  $
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
IOBuf::spaceFill
Description:
   Class: IOBuf.
   Set the fill character to space (' '). This is used when a 
   number is converted to an ASCII digit string, and the width 
   specification (setw) is wider than the digit string, spaces are 
   added to the front of the string to pad it out to the requested 
   length.
*/
IOBuf& spaceFill(IOBuf& b)
{
	b.fill = ' ';
	return b;
}

