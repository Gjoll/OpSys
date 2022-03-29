/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:46  $
  $Workfile:   cmdsub1.cpp  $
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
#include <Command.h>
#include <CmdHandler.h>
#include <CmdSub.h>
/* 
CmdSub::execute
Description:
   Class: CmdSub.
   Called when a Command.handler object that this CmdSub object is 
   linked to parses a command with the same command name as this 
   object.
   When this occurs, call the subsystem Command.handler to handle 
   all commands until the terminating ')' is reached.
Parameters:
   in                  The input CmdPipe. This is where input 
                       commands are parsed.
   out                 The output CmdPipe. This is where responses 
                       to commands are written.
*/
void CmdSub::execute(register CmdPipe* in, CmdPipe* out)
{
	short nesting = in->inNestLevel();
	while (in->inNestLevel() >= nesting) {
		subSystem->parse(in, out);
		while (in->inNestLevel() > nesting)
			*in >> flush;
	}
}

