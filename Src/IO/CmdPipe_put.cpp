/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:38  $
  $Workfile:   cmdpipe1.cpp  $
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
#include <CmdPipe.h>
/* 
CmdPipe::put
Description:
   Class: CmdPipe.
   Put a character onto CmdPipe output pipe. This is called by the 
   formatted output routines of the IOBuf parent class.
   outParens keeps track of the number of open parens minus the 
   number of close parens.
Parameters:
   c                   is the character to write to the pipe.
*/
Bool CmdPipe::put(char c)
{
	Bool retVal;
	switch (c)
	{
	case '(' :
		outParens += 1;
		retVal = CPipe::put(c);
		break;
	case ')' :
		if (outParens > 0)
			outParens -= 1;
		retVal = CPipe::put(c);
		break;
	default:
		retVal = CPipe::put(c);
		break;
	}
	return(retVal);
}

