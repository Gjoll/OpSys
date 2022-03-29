/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:30  $
  $Workfile:   Base.h  $
*/
#ifndef BASE_H
#define BASE_H
#include <OsConfig.h>
#include <OsAssert.h>
#define INIT 0x2715
#define UNINIT 0x7159

/* 
Base
Description:
   This is the base class of all OpSys objects. If provides a 
   means of determining if an object has been constructed or not.
   The user should never create objects of class Base.
Data:
   initialized         Set to a constant pattern when constructed.
Methods:
   initErr             Called by checkInt() when object has not 
                       been constructed. Prints out error message.
   checkInit           Called to verify that object has been 
                       initialized. If initialized has not been 
                       set properly, an error message is printed. 
                       If NDEBUG set, checkInit() is a null method 
                       and does nothing.
   If NDEBUG is NOT set, then the debug object must exist.
*/

class Base
{
 private:
#ifndef NDEBUG
  short initialized;
  void initErr();
 public:
  Base();
  ~Base();
  void checkInit();
#else
 public:
  void checkInit() {;};
#endif
};


#endif
