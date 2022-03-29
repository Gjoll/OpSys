/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:34  $
  $Workfile:   CmdHandler.h  $
*/
#ifndef CMDHANDLER_H
#define CMDHANDLER_H
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
#include <CmdPipe.h>
#include <OsTypes.h>
/* 
CmdHandler
Description:
   Parent Class: CmdHdr.
   Class CmdHandler defines an object whose purpose is to read 
   from a CmdPipe a command name that matches any of the names of 
   the Command Class objects that are linked to this object. (When 
   Objects of class Command are created they are automatically 
   linked onto the list of a specified CmdHandler object.)
            ------------
           | CmdHandler |
            ------------
                  |
                -----------
               | Command 1 |
                -----------
                  |
                -----------
               | Command 2 |
                -----------
                  |
                -----------
               | Command 3 |
                -----------
   If CmdHandler finds a match, then it calls the method 
   Command::execute for that object. Any serial command responses 
   are sent via the second, output, CmdPipe that CmdHandler uses. 
   The 2 CmdPipes are passed into in the Parse method as 
   parameters. These 2 CmdPipes are serial input/output streams.
   Commands always starts immediately after a open paren '(' and 
   continues until it finds a closed paren ')' or comma ','.
   If the Command object expects any information after the command 
   name, it is its responsibility to read the pipe and parse that 
   information.
   eg "(command name, option 1, option 2, ... option x)
Usage:
   #include <CmdHandler.h>

   CmdHandler cmdHandler;

Methods:
   CmdHandler::check   Search through Command list for a command 
                       with the same ASCII name as the token read 
                       from the input CmdPipe.
   CmdHandler::link    Link an object of class Command into the 
                       Command linked list for this object.
   CmdHandler::parse   Parse the input CmdPipe for one input 
                       token. A token is a string of characters, 
                       started with a '(', and terminated by a 
                       ')', or ','. Calls CmdHandler::check when a 
                       token is found.
*/
class CmdHandler : public CmdHdr
{
 private:
 protected:
  Bool check(const char*, CmdPipe* in, CmdPipe* out);
 public:
  CmdHandler();
  ~CmdHandler();

  void link(Command*);
  void parse(CmdPipe* in, CmdPipe* out);
};

#endif
