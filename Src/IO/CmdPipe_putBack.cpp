/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:42  $
  $Workfile:   cmdpipe5.cpp  $
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
CmdPipe::putBack
Description:
   Class: CmdPipe.
   Put one character back onto input pipe. If successful, next 
   get() call will return this character. If there is no room in 
   the CmdPipe to put the character back onto the pipe, False is 
   returned and the character is not put back onto the pipe; 
   Otherwise True is returned.
Parameters:
   c                   is the character to put back.
*/
Bool CmdPipe::putBack(char c)
{
	Bool retVal;
	retVal = CPipe::putBack(c);
	if (retVal == OSTrue)
		switch (c)
		{
		        case '(' :
			      if (inParens > 0)
				      inParens -= 1;
			      break;
			case ')' :
			    inParens += 1;
			    break;
		}
	return retVal;
}

