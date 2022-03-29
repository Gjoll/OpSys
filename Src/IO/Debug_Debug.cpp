/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:56  $
  $Workfile:   debug.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <Pipe.h>
#include <IoBuf.h>
#include <CPipe.h>
#include <debug.h>

/* 
Debug::spin
Description:
   Class: Debug.
   spin() implements a crude spinning cursor, useful for letting 
   the user know that the system is still functioning during long 
   operations. The serial characters that comprise the cursor are 
   written to debug for output.
*/

void Debug::spin()
{
	static short pos = 0;
	static char positions[] = {'\\','|','/','-'};
	*this << '\b' << positions[pos] << flush;
	pos = (pos + 1) & 0x3;
}

/* 
Debug::get
Description:
   This is a dummy function. It does nothing.
*/
Bool Debug::get(char*)
{
	return OSFalse;
}

/* 
Debug::put
Description:
   This is a dummy function. It does nothing.
*/
Bool Debug::put(char)
{
	return OSFalse;
}

/* 
Debug::doFlush
Description:
   This is a dummy function. It does nothing.
*/
Bool Debug::doFlush()
{
	return OSFalse;
}

/* 
Debug::putBack
Description:
   This is a dummy function. It does nothing.
*/
Bool Debug::putBack(char)
{
	return OSFalse;
}

/* 
Debug::Debug
Description:
   Debug constructor.
*/
Debug::Debug()
{
	current = this;
}

/* 
Debug::~Debug
Description:
   Debug destructor.
*/
Debug::~Debug()
{
	current = 0;
}

Debug* Debug::current;
