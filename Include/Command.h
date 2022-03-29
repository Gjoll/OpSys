/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:10  $
  $Workfile:   Command.h  $
*/

#ifndef COMMAND_H
#define COMMAND_H

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
#include <CmdHdr.h>

/* 
Command
Description:
   Parent Class: CmdHdr.
   Class command is the base class for all classes that are serial 
   command processors. Each time an object of class command is 
   created/constructed, it is linked to an object of class 
   CmdHandler. When that CmdHandler reads a serial command, it 
   searches through it's list of Command objects for one with the 
   same ASCII name as the command read. If found, the virtual 
   Command::execute() method for that object is called.
   No objects of class Command should ever be created. It is a 
   'template' for derived classes.
Data:
   cmdSum              16 bit additive checksum of the ascii 
                       command that this object represents. This 
                       is put here to speed up searching of the 
                       command list.
   cmdStr              Pointer to ASCII string that is the name of 
                       this command.
Methods:
   Command::Command    Constructor. Save name of command, 
                       calculate checksum and link into CmdHandler 
                       command list.
   Command::execute    This method is called from class CmdHandler 
                       when a string is read from the input 
                       CmdPipe that matches *cmdStr.
*/

class Command : public CmdHdr
{
  friend class CmdHandler;
 private:
 protected:
  int cmdSum;
  const char* cmdStr;
  virtual void execute(CmdPipe* in, CmdPipe* out) = 0;
 public:
  Command(CmdHandler*, const char*);
  ~Command();
};

#endif
