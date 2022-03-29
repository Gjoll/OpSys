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
  $Workfile:   cmdhan2.cpp  $
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
#include <CmdHandler.h>
#include <Command.h>
#include <OsTypes.h>
/* 
CmdHandler::check
Description:
   Class: CmdHandler.
   CmdHandler::check() will search the Command objects that are 
   linked to this object. Each Command.has a name associated with 
   it. It that name matches the comparison string passed into 
   check, then the virtual execute method for that object is 
   called, and True is returned. Otherwise if no match is found, 
   False is returned.
Parameters:
   cmpStr              is the string to compare the command names 
                       against. The command with the same command 
                       name as *cmdStr will get executed.
   in                  is the input command pipe. This is where 
                       the commands and parameters to the commands 
                       are read from.
   out                 is the command response pipe. This is where 
                       responses to    the commands are written.
*/

/*
1. Compute checksum for comparison string. Each command object has 
additive checksum of string, to help speed up string 
comparison.
2. Iterate through each Command object linked to this.
3. If checksum of comparison string and command object are the same 
then check 2 strings byte by byte for 'sameness'.
4. If 2 strings  are identical, call virtual execute method for 
command object and return True.
5. Get next Command object.
6. If no match found, return False.
*/

Bool CmdHandler::check(const char* cmpStr, CmdPipe* in, CmdPipe* out)
{
	int cmpSum = 0;
	const char* cmdPtr;
	const char* cmpPtr = cmpStr;
	Command* comPtr = (Command*) next;
	while (*cmpPtr != '\0')						//1
		cmpSum += *cmpPtr++;
	while (comPtr != (Command*) this)				//2
	{
		if (cmpSum == comPtr->cmdSum)				//3
		{
 			cmdPtr = comPtr->cmdStr;
			cmpPtr = cmpStr;
			while ((*cmdPtr != '\0') && (*cmdPtr++ == *cmpPtr++));
			if ((*cmdPtr == '\0') && (*cmpPtr == '\0'))	//4
			{
				comPtr->execute(in, out);
				return(OSTrue);
			}
		}
		comPtr = (Command*) comPtr->next;			//5
	} 
	return(OSFalse);							//6
}

