/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:36  $
  $Workfile:   cmdint1.cpp  $
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
#include <Command.h>
#include <CmdHandler.h>
#include <CmdInt.h>

/* 
CmdInt::execute
Description:
   Class: CmdInt.
   CmdInt::execute is called when the Command.handler object that 
   this CmdInt object is linked to gets a command with the same 
   name as this variable.
   This method then either a) sets the CmdInt object to the values 
   passed in the input CmdPipe, and returns the status of the set 
   operation or b) returns the current setting of the CmdInt if no 
   values are passed to set it to.
   The remaining data in the input pipe should be either ')' 
   meaning that the user wants to get the current setting for this 
   variable, or {settings}) where settings is a comma separated 
   list of settings.
   There should be exactly as many settings as there are elements 
   in *values, and each setting must be with in the values 
   established by the bounds array.
Parameters:
   in                  is the input command pipe. This is where 
                       the commands and parameters to the commands 
                       are read from.
   out                 is the command response pipe. This is where 
                       responses to the commands are written.
   Examples:
   Assume Name is the ascii name for this CmdInt object, there are 
                       3 elements and the bounds array specifies 
                       that each element of the array must be in 
                       the range 1..3.
   #                   Command         Response
   1                   (Name,1)        (Name,badCount)
   2                   (Name,1,2,4)        (Name,outOfBounds)
   3                   (Name,3,2,1)        (Name,ok)
   4                   (Name)          (Name,3,2,1)

   1 The command specified too few parameters. This CmdInt is an 
                       array of 3 elements, only one value was 
                       set. This caused the badCount message to be 
                       returned.

   2 The command tried to set the third element of CmdInt to a 
                       value that was too large. The bounds array 
                       passed to CmdInt specified that each 
                       element was to be in the range 1..3. This 
                       caused the outOfBounds message to be 
                       returned.

   3. This command was correct. The CmdInt was set to 3,2,1. ok is 
                       returned.

   4. This command was correct. Since nothing was set, the current 
                       values of the CmdInt were returned.
*/

/*
1. Get the integer values from the input stream until either a 
character not equal to ',' is read as the separator between 
numbers, or as many numbers as integers in this CmdInt are read.
2. If there are neither 0, or length (# ints in CmdInt) numbers read 
in the input stream, then flush the input stream to the end of 
this command and put "badCount" error message into the output stream.
3. If setting CmdInt values, verify that each value is in the bounds 
set by the bounds array. If it is not then put "outOfBounds" error 
into the output pipe.
4. Everything all right, then set the CmdInt array to the passed 
values, and put "ok" into the output pipe.
5. Put the current setting of CmdInt into the output pipe.
*/

void CmdInt::execute(CmdPipe* in, CmdPipe* out)
{
	char term;
	int newValues[MAX_CMD_INTS + 1];
	short count = 0;
	short index;
	*in >> term;
	while ((count < length) && (term == ',')) {			//1
		*in >> newValues[count];
		if ((in->fail() == OSFalse) && (count < MAX_CMD_INTS))
			count += 1;
		else {
			count = -1;
			break;
		}
		*in >> term;
	} 
	if (								//2
		((count != 0) && (count != length)) ||
		(term != ')')
	) {
		*in << flush;
		if (term == '(')
			*in << flush;
	 	*out << '(' << cmdStr << ",badCount)";
		return;
	}
	if (count != 0)
	{								//3
		if (bounds != 0)
		{
			const int* bPtr = bounds;
			for(index = 0; index < count; index++)
			{
				int lower = *bPtr++;
				int upper = *bPtr++;
				if ((newValues[index] < lower) ||
				    (newValues[index] > upper))
				{
 				 	*out << '(' << cmdStr <<
						",outOfBounds)";
					return;
				}
			}
		}
		for(index = 0; index < count; index++)			//4
			values[index] = newValues[index];
	 	*out << '(' << cmdStr << ",ok)";			//5
		return;
	}
	*out << '(' << cmdStr;						//6
	for (count = 0; count < length; count++)
		*out << ',' << values[count];
	*out << ')';
}

