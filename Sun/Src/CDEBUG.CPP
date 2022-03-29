/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision:   2.1  $
  $Modtime:   01 May 1993 09:34:24  $
  $Workfile:   cdebug.cpp  $
*/
#include <cdebug.h>
#include <opsys.h>
#include <stdio.h>
/* 
CDebug::doFlush
Description:
   This method does noting. The flush manipulator does nothing for 
   CDebug objects.
*/
Bool CDebug::doFlush()
{
	os.swapOff();
	fflush(stderr);
	os.swapOn();
	return True;
}

/* 
CDebug::put
Description:
   Output one character. This method is not called by the user. 
   but by the formatted I/O routines of the IOBuf parent class.
*/
Bool CDebug::put(char c)
{
	os.swapOff();
	fputc(c, stderr);
	os.swapOn();
	return(True);
}

