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
  $Workfile:   CPipe.h  $
*/
#ifndef CPIPE_H
#define CPIPE_H
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <Pipe.h>
#include <IoBuf.h>
/* 
CPipe
Description:
   Parent Class: CPipe.
   Class CPipe implements a character pipe with all the character 
   formatting inherent to IOBuf. Only character data can be put 
   onto or read from the pipe. Binary numbers are converted to 
   digit strings for writing. Digit strings can also be read from 
   and converted to binary numbers. None of the put/get Pipe 
   functions are available directly to the user. Only the IOBuf 
   I/O functions, which then call the put and get methods.
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

   #include <CPipe.h>
   #define CPIPE_LENGTH ???

   extern char cPipeBuffer[CPIPE_LENGTH];
   Cpipe cPipe(cPipeBuffer, sizeof(cPipeBuffer), "CPipe Name");

Methods:
   CPipe::CPipe        CPipe constructor.
   CPipe::~CPipe       CPipe Destructor.
   CPipe::get          Get one character from the CPipe.
   CPipe::put          Put one character onto the CPipe.
*/
class CPipe : public IOBuf, private Pipe
{
 private:
 protected:
  Bool get(char*);
  Bool put(char);
  Bool doFlush();
 public:
  CPipe(char*, int length, BFlags = OS_FIFO, const char* = 0);
  ~CPipe();
  Bool putBack(char);
  Bool putBack(char*);
};

#endif
