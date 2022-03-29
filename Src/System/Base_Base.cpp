/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:18  $
  $Workfile:   base.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <debug.h>
#ifndef NDEBUG

/* 
Base::Base
Description:
   Class Base.
   Base class constructor.
   This sets the initialized flag, so that subsequent calls to 
   Base::checkInit will not fail. This is only compiled if the 
   compile flag NDEBUG is undefined.
*/

Base::Base()
{
  initialized = INIT;
};


/* 
Base::~Base
Description:
   Class Base.
   Base class destructor
   This resets initialized so that Base::checkInit will fail if 
   called on any derived object from this class. This is only 
   compiled if the compile flag NDEBUG is undefined.
*/

Base::~Base()
{
  initialized = UNINIT;
};


/* 
Base::initErr
Description:
   Class Base.
   Called from Base::checkInit if initialized flag is not set 
   properly (i.e. Base::Base not called for this object yet). 
   Print out error message and exit. This is only compiled if the 
   compile flag NDEBUG is undefined.
*/

void Base::initErr()
{
  if (initialized == UNINIT) {
    (*Debug::current) << "Object was used after it's destructor\n\r"
      << "was called. Program fatal error\n\r";
    os.exit(-100);
  } else {
    (*Debug::current) << "Object was used before it was properly\n\r"
      << "initialized. Program fatal error\n\r";
    os.exit(-101);
  }
};

#endif
