/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:10  $
  $Workfile:   iobuf35.cpp  $
*/
#define TYPE short
/* 
IOBuf::operator<<6
Description:
   Class: IOBuf.
   Write a short to the IOBuf, converting it to ASCII as it is 
   copied. If setw(width) has been called, then the written string 
   is padded out to the length specified, by adding fill chars 
   onto the end. The fill char is set by the fill manipulator. The 
   base of the output string defaults to 10, but can be set to 
   2,8,10,16 by the manipulators IOBuf::dec, IOBuf::oct, 
   IOBuf::bin, and IOBuf::hex.
   The field width is reset to 0 after this call and the base is 
   reset to 10.
*/
#include <wsigprot.h>

