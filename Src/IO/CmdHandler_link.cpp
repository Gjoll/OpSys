/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:42  $
  $Workfile:   cmdhan3.cpp  $
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
CmdHandler::link
Description:
   Class: CmdHandler.
   CmdHandler::link is called to link an object of class Command 
   to a Command.handler. In this way, if the CmdHandler reads a 
   command that matches the Command objects name/string, the 
   command objects virtual method Command::execute() will be 
   called.
   There is no order implied in the command list. Multiple 
   commands with the same command string will cause unpredictable 
   results.
Parameters:
   element             is the Command object to link to this 
                       CmdHandler.
*/

void CmdHandler::link(Command* element)
{
	os.swapOff();
	element->next = (CmdHdr*) this;
	element->last = last;
	last->next = (CmdHdr*) element;
	last = (CmdHdr*) element;
	os.swapOn();
}


