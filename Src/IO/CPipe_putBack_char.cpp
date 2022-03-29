/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:54  $
  $Workfile:   cpipe4.cpp  $
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
CPipe::putBack1
Description:
   Class: CPipe.
   Put one character onto FRONT of CPipe. If the operation was 
   sucessful the next CPipe::get() call will return this 
   character. If the pipe is full, then False is returned and the 
   character is NOT put back onto the pipe; Otherwise True is 
   returned.
Parameters:
   c                   is the character to write onto the pipe.
*/

Bool CPipe::putBack(char c)
{
	return (Pipe::putBack(c) == OS_DONE) ? OSTrue : OSFalse;
}

