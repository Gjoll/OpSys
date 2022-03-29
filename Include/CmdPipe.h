/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.
*/

/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:04  $
  $Workfile:   CmdPipe.h  $
*/

#ifndef CMDPIPE_H
#define CMDPIPE_H

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

/* 
CmdPipe
Description:
   Parent Class CPipe$.
   Class CmdPipe implements a bidirectional (input/output) 
   character pipe (CPipe) with a few additional methods added to 
   keep track of commands enclosed in parens.
   CmdPipes are used by all Command Processing classes as the 
   input/output streams. Input contains the commands, output will 
   contain the command responses.
   Tasks blocked on a pipe can become unblocked in FIFO order, or 
   task priority order (highest priority tasks before lower 
   priority). The user controls this by the flags setting options 
   OS_FIFO, or OS_PRIORITY in the pipe constructor. Setting the 
   OS_FIFO bit in flags will make this pipe a FIFO pipe, and tasks 
   will become unblocked in FIFO order. The task that was blocked 
   first will become unblocked first.
   Setting the OS_PRIORITY bit will make it a priority pipe. 
   Highest priority tasks will become unblocked before lower 
   priority tasks.
   If both OS_PRIORITY and OS_FIFO are set, then if will be a FIFO 
   pipe. The default value is OS_FIFO.
Usage:
   #include <CmdPipe.h>
   #define CMD_PIPE_BUFFER_LENGTH ???
   extern char cmdPipeBuffer[CMD_PIPE_BUFFER_LENGTH];
   CmdPipe cmdPipe(cmdPipeBuffer, sizeof(cmdPipeBuffer), 
                       "CmdPipe-Name");
Data:
   inParens            Number of opening parens - number of close 
                       parens read in input.
   outParens           Number of opening parens - number of close 
                       parens written to output.
Methods:
   CmdPipe::CmdPipe    Class constructor.
   CmdPipe::~CmdPipe   Class destructor.
   CmdPipe::get        Get one character from input CmdPipe. This 
                       is a private routine.
   CmdPipe::put        Put one character to output CmdPipe. This 
                       is a private routine. CmdPipe::doFlushFlush 
                       input CmdPipe. That is, read until inParens 
                       is 0, such that the next open paren is the 
                       start of a new command.
   CmdPipe::getToken   Get one token from the input CmdPipe.
   CmdPipe::inNestLevel    Return value of inParens.
   CmdPipe::outNestLevel   return value of outParens.
   CmdPipe::putBack    Put one character back onto the input 
                       CmdPipe. The next CmdPipe::get call will 
                       retrieve this character. Only one character 
                       can be put back before a CmdPipe::get must
   occur.
*/

class CmdPipe : public CPipe
{
 private:
  short inParens;
  short outParens;
 protected:
  Bool get(char* c);
  Bool put(char c);
  Bool doFlush();
 public:
  CmdPipe(char*, int length, BFlags = OS_FIFO, const char* = 0);
  ~CmdPipe();
  char getToken(char*, short);
  short inNestLevel();
  short outNestLevel();
  Bool putBack(char);
};

#endif
