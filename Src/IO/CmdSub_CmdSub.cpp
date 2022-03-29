/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:44  $
  $Workfile:   cmdsub.cpp  $
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
CmdSub::CmdSub
Description:
   Class: CmdSub.
   CmdSub constructor.
   Link This object into master Command.handler, store pointer to 
   subsystem Command.handler, and store pointer to name of this 
   command.
Parameters:
   master              Master Command.handler. This is the command 
                       handler that will call this object when it 
                       parses its command name.
   sub                 This is the CmdHandler that is called by 
                       this object after this object is called by 
                       the master command processor.
   str                 This is the command name of this 
                       CmdSubobject.
*/
CmdSub::CmdSub(CmdHandler* master, CmdHandler* sub,
	const char* str) :
	Command(master, str), subSystem(sub)
{
}

/* 
CmdSub::~CmdSub
Description:
   Class: CmdSub.
   CmdSub Destructor.
*/
CmdSub::~CmdSub()
{
}

