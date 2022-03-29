/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:28  $
  $Workfile:   wsigprot.h  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OsTypes.h>
#include <IoBuf.h>

IOBuf& IOBuf::operator<<(TYPE num)
{
  char buffer[MAXDIGITS];
  char* str = buffer;
  short count = 0;
  short sign = 1;
  short offset;
  short iWidth = width; 
  successFlag = OSTrue;
  if (num < 0)
    sign = -1;
  do {
       offset = (short) (num % base);
       if (offset < 0) offset = -offset;
       *str++ = (char) cnvTab[offset];
       num /= base;
     } while ((count++ < sizeof(buffer) - 1) && (num != 0));
  if (sign == -1) {
		    count += 1;
		    if (fill != ' ')
		      operator<<('-');
		  }
  while ((successFlag == OSTrue) && (iWidth > count++))
    operator<<( fill);
  if ((successFlag == OSTrue) && (sign == -1) && (fill == ' '))
    operator<<('-');
  while ((successFlag == OSTrue) && (str != buffer))
    operator<<(*--str);
  width = 0;
  return(*this);
}

