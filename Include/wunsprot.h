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
  $Workfile:   wunsprot.h  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <IoBuf.h>
#include <OsTypes.h>

IOBuf& IOBuf::operator<<(unsigned TYPE number)
{
  char buffer[MAXDIGITS];
  char* str = buffer;
  short count = 0;
  unsigned TYPE num = number;  
  short iWidth = width;
  successFlag = OSTrue;
  do {
       *str++ = (char) (cnvTab[num % base]);
       num /= base;
     } while (
	      (successFlag == OSTrue) &&
	      (count++ < sizeof(buffer) - 1) &&
	      (num > 0)
	      );
  while ((successFlag == OSTrue) && (iWidth > count++))
    operator<<(fill);
  while ((successFlag == OSTrue) && (str != buffer))
    operator<<(*--str);
  width = 0;
  return(*this);
}
