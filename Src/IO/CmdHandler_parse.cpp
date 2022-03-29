/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:40  $
  $Workfile:   cmdhan1.cpp  $
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
#include <CmdHdr.h>
#include <OsTypes.h>
#include <CmdHandler.h>
/* 
CmdHandler::parse
Description:
   Class: CmdHandler.
   Parse parses the input CmdPipe for a command, and attempts to 
   find a command linked to this CmdHandler that has the same name 
   as the token just read.
   If no matching command object is found, the response 
   '({Cmd},unknown)' is sent out the output CmdPipe. {Cmd} is the 
   unknown command just read in.
   If a matching command object is found, then the execute method 
   for that object is called. It is the responsibility of that 
   object to parse the input CmdPipe until the terminating ')' is 
   reached.
   A command is a string of characters, started by a '(' and 
   terminated by either a ')' or ','. All characters up to the 
   opening '(' are thrown away.
   Maximum command length is 20.
Parameters:
   in                  is the input command pipe. This is where 
                       the commands and parameters to the commands 
                       are read from.
   out                 is the command response pipe. This is where 
                       responses to the commands are written.
*/
#define MAX_COMMAND_LENGTH	20

void CmdHandler::parse(CmdPipe* in, CmdPipe* out)
{
	char token[MAX_COMMAND_LENGTH];
	char terminator;
	do {
		*in >> terminator;
	} while ((terminator != '(') && (terminator != ')'));
	if (terminator != ')')
		if (in->getToken(token, sizeof(token))) {
			if (
			   (terminator != '(') ||
			   (!check(token, in, out))
			) {
				*in >> flush;
				*out << terminator << token << ",unknown)";
			}
		}
}

