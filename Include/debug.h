/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:10  $
  $Workfile:   debug.h  $
*/
#ifndef DEBUG_H
#define DEBUG_H
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <PtrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <Pipe.h>
#include <IoBuf.h>

/* 
Debug
Description:
   Parent Class: IOBuf.
   The Debug class implements a means of typing out debug 
   messages.
   Any data written to an object derived from class Debug will be 
   written to some serial stream similar to stderr. The actual 
   implementation of class Debug is port dependent. Class Debug is 
   a pure class. All instances must be of classes derived from 
   Debug.
   There should be one and only one object of a class derived from 
   Debug created. This object must be named "debug", and is 
   referred to as the debug object. This object is used to print 
   out debug information at run time.
*/
class Debug : public IOBuf
{
 protected:
  Bool get(char*);
  Bool put(char);
  Bool doFlush();
 public:
  static Debug* current;
  Debug();
  ~Debug();
  Bool putBack(char);
  virtual void spin();
};

#endif
