/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:16  $
  $Workfile:   assert.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <debug.h>
#include <OpSys.h>
 
/* 
Assert
Description:
   This is the function which the assert macro calls if the 
   condition specified in the macro is false/0. Assert prints out 
   an error message.
   All assert messages are written to the debug object.
Parameters:
   fileName            is a string == filename of file where the 
		       assert() is located.
   line                is the line number in the file where the 
		       assert() is located.
*/

void Assert(const char* fileName, int line)
{
#ifndef NDEBUG
	Bool lckFlag = OSFalse;
	if (os.locked())
	{
		lckFlag = OSTrue;
		os.unLock();
	}
	(*Debug::current) << ("Assertion Failed. File ") << fileName
		<< " Line " << dec << line << endl;
	if (lckFlag == OSTrue)
		os.lock();
#endif
}


