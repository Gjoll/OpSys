/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.
*/

/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:08  $
  $Workfile:   CmdTask.h  $
*/

#ifndef CMDTASK_H
#define CMDTASK_H

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <CmdHdr.h>
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

#define CMD_STACK_LENGTH 512            /* length of stack. */
#define CMD_PRIORITY 251                /* low priority. */
/*
CmdTask
Description:
	Parent Class STask$.
	Class CmdTask implements a STask that calls an object of Class
	CmdHandler to parse in input CmdPipe for commands. This task is
	automatically started at construction.
	The input and output CmdPipes to read and write, and the
	CmdHandler object to call are all passed in as constructor
	arguments. As with all classes derived from Task, this has its
	own stack.
Usage:

	#include <CmdTask.h>

	extern CmdHandler cmdHandler;
	extern CmdPipe input;
	extern CmdPipe output;

	CmdTask cmdTask(&cmdHandler, &input, &output);
*/

class CmdTask : private Task
{
 private:
  STAK stack[CMD_STACK_LENGTH];
 protected:
  CmdHandler* cmdHandler;
  CmdPipe* in;
  CmdPipe* out;
  void run();
 public:
  CmdTask(CmdHandler*, CmdPipe* in, CmdPipe* out);
  ~CmdTask();
};

#endif
