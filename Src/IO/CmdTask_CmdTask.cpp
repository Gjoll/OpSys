/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:48  $
  $Workfile:   cmdtask.cpp  $
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
#include <CmdHandler.h>
#include <CmdTask.h>
#include <CmdHdr.h>
/* 
CmdTask::CmdTask
Description:
   Class: CmdTask.
   CmdTask constructor. Initialize all data, and parent Task 
	class. After everything is initialized, this task is started
   (Task::start()).
Parameters:
   han                 This is the Command.handler that this task 
                       is to call. All this task does is keep 
                       calling han.parse() to parse the input 
                       stream and execute any commands read.
   iIn                 Pointer to input CmdPipe. This is where 
                       commands are read from.
   iOut                Pointer to output CmdPipe. This is where 
                       command responses are written to.
*/

CmdTask::CmdTask(CmdHandler* han, CmdPipe* iIn, CmdPipe* iOut) :
	Task(stack, sizeof(stack), CMD_PRIORITY, "Cmd Handler"),
	in(iIn), out(iOut), cmdHandler(han)
{
	start();
}


/* 
CmdTask::~CmdTask
Description:
   Class: CmdTask.
   CmdTask destructor.
*/

CmdTask::~CmdTask()
{
}

