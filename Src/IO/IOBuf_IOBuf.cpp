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
  $Workfile:   iobuf.cpp  $
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
IOBuf::IOBuf
Description:
   Class: IOBuf.
   IOBuf constructor.
   This sets the default fill to spaces, the numerical base to 10, 
   the output field width to 0, deletes the put back character, 
   and turns off the skip white space flag.
*/

IOBuf::IOBuf()
{
	base = 10;	// bae 10 number output.
	fill = ' ';	// number fill = spaces.
	width = 0;	// print out only digits that are valid.
	successFlag = OSTrue;
	skipWhiteSpace = OSFalse;
}

