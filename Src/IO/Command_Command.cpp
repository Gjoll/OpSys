/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:50  $
  $Workfile:   command.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <CmdHdr.h>
#include <IoBuf.h>
#include <CPipe.h>
#include <CmdPipe.h>
#include <OsTypes.h>
#include <CmdHandler.h>
#include <Command.h>
/* 
Command::Command
Description:
   Class: Command.
   Command constructor.
   This links the Command object to a CmdHandler, stored the 
   command name, and computed the additive checksum of the command 
   name (used to speed up command comparisons).
Parameters:
   main                CmdHandler to link this command to.
   str                 Command name of this command.
*/

Command::Command(CmdHandler* main, const char* str) :
	cmdStr(str)
{
	register const char* cPtr = cmdStr;
	cmdSum = 0;
	while (*cPtr != '\0')
		cmdSum += *cPtr++;
	main->link(this);
}


/* 
Command::~Command
Description:
   Class: Command.
   Command destructor.
*/

Command::~Command()
{
}

