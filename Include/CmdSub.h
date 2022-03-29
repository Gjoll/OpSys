/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:06  $
  $Workfile:   CmdSub.h  $
*/
#ifndef CMDSUB_H
#define CMDSUB_H

#include <Base.h>
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
/* 
CmdSub
Description:
   Parent Class Command$.
   CmdSub class implements a command subsystem. A command 
   subsystem is a bridge between 2 CmdHandler objects. The 
   commands sent are first received by the first Command.handler, 
   the one that the input command pipe is normally parsed by, then 
   if the command name of the CmdSub object is read, all data up 
   to the terminating ')' is read by the second CmdHandler.
   eg.
   Assume 2 CmdHandlers, Cmd1 and Cmd2. A CmdSub object links Cmd1 
   with Cmd2. It has the command name System1.
   (System1(command1)(command2)(command3))
   (System1 is parsed by Cmd1, command1,command2, command3 are 
   parsed by Cmd2.

    --------------
   | CmdHandler 1 |
    --------------
          |
        --------                        --------------
       | CmdSub |--------------------- | CmdHandler 2 |
        --------                        --------------
          |                                  |
        ------------------                   |
       | Other CmdHandler |             --------------
       |     Commands     |            | CmdHandler 2 |
        ------------------             |    Commands  |
          |                             --------------
        ------------------
       | Other CmdHandler |
       |     Commands     |
        ------------------
          |
        ------------------
       | Other CmdHandler |
       |     Commands     |
        ------------------
Usage:
   #include <CmdSub.h>

   extern CmdHandler master;
   extern CmdHandler subSystem;

   CmdSub cmdSub(master, subSystem, "Command Subsystem Name");

Methods:
   CmdSub::CmdSub      Constructor.
   CmdSub::~CmdSub     Destructor.
   CmdSub::execute     is called when the Command.handler that 
                       this object is linked to finds a command 
                       that matches the name of this CmdSub 
                       object.
*/

class CmdSub : public Command
{
 private:
 protected:
  CmdHandler* subSystem;
  void execute(CmdPipe* in, CmdPipe* out);
 public:
  CmdSub(CmdHandler* master, CmdHandler* subSystem, const char* cmdStr);
  ~CmdSub();
};

#endif
