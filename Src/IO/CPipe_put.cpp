/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:52  $
  $Workfile:   cpipe1.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <Pipe.h>
#include <IoBuf.h>
#include <CPipe.h>
/* 
CPipe::put
Description:
   Class: CPipe.
   Put one character onto CPipe. This will be called by the 
   formatted I/O routines of IOBuf.
Parameters:
   c                   is the character to write onto the pipe.
*/

Bool CPipe::put(char c)
{
	Pipe::put(c);
	return(OSTrue);
}

