/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/

/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:54  $
  $Workfile:   cdebug.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <MemBuffer.h>
#include <opSys.h>
#include <OsTypes.h>
#include <ioBuf.h>
#include <cdebug.h>
#include <conio.h>

/* 
CDebug::get
Description:
   Class: CDebug.
   This method does nothing. CDebug objects are output only. False 
   is always returned.
*/

Bool CDebug::get(char*)
{
	return OSFalse;
}



/* 
CDebug::doFlush
Description:
   Class: CDebug.
   Flush out all CDebug serial data.
*/


Bool CDebug::doFlush()
{
	os.swapOff();
	fprintf(stderr, strBuf);
	fflush(stderr);
	os.swapOn();
	str << flush;
	return OSTrue;
}



/* 
CDebug::put
Description:
   Class: CDebug.
   Output one character. This method is not called by the user. 
   but by the formatted I/O routines of the IOBuf parent class.
*/

Bool CDebug::put(char c)
{
	str << c;
	if ((c == '\n') || (str.strlen() >= sizeof(strBuf) - 2))
		doFlush();
	return(OSTrue);
}



/* 
CDebug::putBack
Description:
   Class: CDebug.
   This method does nothing. CDebug objects are output only. False 
   is always returned.
*/

Bool CDebug::putBack(char)
{
	return OSFalse;
}



/* 
CDebug::CDebug
Description:
   Class: CDebug.
   CDebug constructor.
*/
CDebug::CDebug() :
	str(strBuf, sizeof(strBuf))
{
}



/* 
CDebug::~CDebug
Description:
   Class: CDebug.
   CDebug destructor.
*/
CDebug::~CDebug()
{
}




