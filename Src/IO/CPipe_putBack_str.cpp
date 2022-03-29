/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:56  $
  $Workfile:   cpipe5.cpp  $
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
CPipe::putBack2
Description:
   Class: CPipe.
   Put a null terminated string onto FRONT of CPipe. If there is 
   not room to put back the entire string onto the pipe, then 
   False is returned and no part of the string is written to the 
   CPipe; Otherwise True is returned.
   If the operation was successful, the next get call will return 
   the first character of this string.
Parameters:
   c                   is the string to write onto the pipe.
*/
extern "C" int strlen(const char*);

Bool CPipe::putBack(char* c)
{
	return (Pipe::putBack(c, strlen(c)) == OS_DONE) ? OSTrue : OSFalse;
}

