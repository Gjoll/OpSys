
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
  $Workfile:   cmdsys.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <Pipe.h>
#include <IoBuf.h>
#include <CPipe.h>
#include <CmdPipe.h>
#include <Command.h>
#include <CmdHandler.h>
#include <CmdSub.h>
#include <CmdSys.h>
/* 
CmdSystem::CmdSystem
Description:
   Class: CmdSystem.
   CmdSystem constructor.
   Link CmdSystem object to a Command.handler and set the command 
   name to sys.
Parameters:
   main                The CmdHandler to link this object to.
*/
CmdSystem::CmdSystem(CmdHandler* main) :
	CmdSub(main, &system, "sys"),
	system(),
	sysInfo(&system, "all"),
	taskInfo(&system, "tasks"),
	blockerInfo(&system, "blocks")
{
	main->link(this);
}

/* 
CmdSystem::~CmdSystem
Description:
   Class: CmdSystem.
   CmdSystem destructor.
*/
CmdSystem::~CmdSystem()
{
}

void SysInfo::execute(CmdPipe* in, CmdPipe*)
{
	*in >> flush;
	os.taskInfo();
	os.blockInfo();
}

// TaskInfo:: execute
// Called when a Command.handler object that this SysPrintInfo object is linked
// to gets a command with the same name as this variable.
void TaskInfo::execute(CmdPipe* in, CmdPipe*)
{
	*in >> flush;
	os.taskInfo();
}

// BlockerInfo:: execute
// Called when a Command.handler object that this BlockInfo object is linked
// to gets a command with the same name as this variable.
void BlockerInfo::execute(CmdPipe* in, CmdPipe*)
{
	*in >> flush;
	os.blockInfo();
}
