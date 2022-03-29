/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:40  $
  $Workfile:   cmdpipe2.cpp  $
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
CmdPipe::get
Description:
   Class: CmdPipe.
   Get one character from CmdPipe input pipe. This method is used 
   by the formatted input routines of the IOBuf parent class.
Parameters:
   c                   is where the character read from the pipe 
                       is written/returned to.
*/
Bool CmdPipe::get(char* c)
{
	Bool sucFlag;
	skipWhiteSpace = OSTrue;
	sucFlag = CPipe::get(c);
	if (sucFlag)
		switch (*c)
		{
		case '(' :
			inParens += 1;
			break;
		case ')' :
			if (inParens > 0)
				inParens -= 1;
			break;
		}
	return sucFlag;
}

