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
  $Workfile:   cpipe2.cpp  $
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
CPipe::get
Description:
   Class: CPipe.

   get one character from the CPipe. This routine will be called 
   by the formatted I/O methods of IOBuf.
Parameters:
   c                   is a pointer to a character to store the 
                       character from the pipe into.
*/

Bool CPipe::get(char* c)
{
	return (Pipe::get(c) == OS_DONE) ? OSTrue : OSFalse;
}

