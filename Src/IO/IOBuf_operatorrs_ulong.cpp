/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:06  $
  $Workfile:   iobuf27.cpp  $
*/
#define TYPE long
/* 
IOBuf::operator>>11
Description:
   Class: IOBuf.
   Read an unsigned long from the IOBuf. The base defaults to 
   decimal, but can be changed by the manipulators  IOBuf::dec, 
   IOBuf::oct, IOBuf::bin, and IOBuf::hex. No leading minus signs 
   are allowed. Characters are read from the IOBuf and converted 
   until a non digit is found, or
   until the width is exhausted (set via the setw manipulator). If 
   base is 16, then A..F and a..f are considered digits.
*/
#include <runsprot.h>

