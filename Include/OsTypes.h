/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:20  $
  $Workfile:   OsTypes.h  $
*/
#ifndef OSTYPES_H
#define OSTYPES_H

// Bool
// This is the data type for any variables that are Boolean
enum Bool {OSFalse, OSTrue};

// elementsof
// This macro will compute the number of elements in any
// array type variable.
#define elementsof(a) (sizeof((a)) / sizeof((a[0])))

// Byte
// 8 bit unsigned.
typedef unsigned char Byte;

#endif
