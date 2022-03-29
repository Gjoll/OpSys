/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:22  $
  $Workfile:   rsigprot.h  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <IoBuf.h>

IOBuf& IOBuf::operator>>(TYPE& num)
{
  int widFlag = (width > 0);
  short sign = 1;
  char c;
  TYPE value;
  num = 0;
  successFlag = OSFalse;

  (*this) >> c;
  if (c == '-')
    sign = -1;
  else
    putBack(c);

  while ((widFlag == 0) || (width-- > 0))
    {
      (*this) >> c;
      if ((c >= '0') && (c <= '9'))
	value = c - '0';
      else if ((c >= 'A') && (c <= 'F'))
	value = c - 'A'+ 10;
      else if ((c >= 'a') && (c <= 'f'))
	value = c - 'a' + 10;
      else
	{
	  putBack(c);
	  break;
	}
      if (value >= base)
	{
	  putBack(c);
	  break;
	}
      successFlag = OSTrue;
      num *= base;
      num += value;
    }
  num *= sign;
  return *this;
}
