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
  $Workfile:   cmdpipe4.cpp  $
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
#include <IoString.h>
#include <CPipe.h>
#include <CmdPipe.h>
/* 
CmdPipe::getToken
Description:
   Class: CmdPipe.
   Get one token from input stream. A token is a of the form 
   '('Name. Name can be any sequence of characters that does not 
   contain '(', ')', ' ', or ','.
Parameters:
   token               is a pointer to a character buffer that the 
                       token read from the command input pipe is 
                       to be stored in.
   len                 is the maximum length of *token.
*/
char CmdPipe::getToken(char* token, short len)
{
	char c;
	IOString string(token, len);
	Bool contFlag = OSTrue;
	string << flush ;
	while (contFlag)
	{
		operator>>(c);
		switch (c) {
		case '(' :
		case ')' :
		case ',' :
			putBack(c);
			contFlag = OSFalse;
			break;
		default:
			string << c;
			break;
		}
	}
	return(c);
}

