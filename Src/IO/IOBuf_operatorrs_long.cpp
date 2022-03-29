/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:02  $
  $Workfile:   iobuf24.cpp  $
*/
#define TYPE long
/* 
IOBuf::operator>>8
Description:
   Class: IOBuf.
   Read a long from the IOBuf. The base defaults to decimal, but 
   can be changed by the manipulators  IOBuf::dec, IOBuf::oct, 
   IOBuf::bin, and IOBuf::hex. A leading minus sign can be 
   included to make the number negative. Characters are read from 
   the IOBuf and converted until a non digit is found, or
   until the width is exhausted (set via the setw manipulator). If 
   base is 16, then A..F and a..f are considered digits.
*/
#include <rsigprot.h>

