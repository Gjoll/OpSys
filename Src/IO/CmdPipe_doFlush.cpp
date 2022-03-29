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
  $Workfile:   cmdpipe3.cpp  $
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
#include <debug.h>
/* 
CmdPipe::doFlush
Description:
   Class: CmdPipe.
   Throw away all characters in input stream until end of command. 
   End of command is detected when as many close parens have been 
   read as open parens.
*/
Bool CmdPipe::doFlush()
{
	char c;
	short nestingLevel = inNestLevel();
	if (nestingLevel > 0)
		while (nestingLevel <= inParens)
			operator>>(c);
	return OSTrue;
}

