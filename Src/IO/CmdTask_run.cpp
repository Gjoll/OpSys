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
  $Workfile:   cmdtask1.cpp  $
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
#include <CmdHdr.h>
#include <CmdHandler.h>
#include <CmdTask.h>
/* 
CmdTask::run
Description:
   Class: CmdTask.
   This is the method that is called by the parent Task class when 
   this task is started. run() runs as its own independent thread 
   of execution with its own stack and CPU time slices. Its 
   function is to keep calling the parse() method of '*cmdHandler' 
   to parse any commands in the input CmdPipe 'in'.
   This task is blocked when there is not any input data in 'in'.
*/
void CmdTask::run()
{
	for (;;)
		cmdHandler->parse(in, out);
}

