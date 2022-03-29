/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:20  $
  $Workfile:   base1.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>

#ifndef NDEBUG
/* 
Base::checkInit
Description:
   Class Base.
   Print out an error message and halt if object has not been 
   constructed. Action is only taken if NDEBUG compile flag is NOT 
   set.
*/

void Base::checkInit()
{
  if (initialized != INIT)
    initErr();
}

#endif

