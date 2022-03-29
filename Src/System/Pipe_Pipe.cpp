/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:20  $
  $Workfile:   pipe.cpp  $
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

/* 
Pipe::Pipe
Description:
   Class Pipe.
   Pipe constructor.
   The Pipe constructor uses an external buffer as the circular 
   data buffer. This allows the user to specify exactly how long 
   the buffer is, and where it exists. This buffer should of 
   course not be used for anything else, nor should it be 
   allocated on the stack if the pipe will continue to exist after 
   the current stack frame is deleted.
   An optional name for this pipe can also be specified. This name 
   is used for debugging purposes only.
Parameters:
   iPipe               is the user defined memory buffer used by 
                       the pipe object to store data that has been 
                       written to the pipe, but not yet read.
   iPipeLength         is the number of bytes in iPipe.
   flags               is a series of bits that control the action 
                       of this pipe. The meaning of the flags are 
                       as follow.
                       OS_FIFO - pipe is a fifo pipe. Tasks that 
                       are blocked on this pipe will become 
                       unblocked in FIFO order.
                       OS_PRIORITY - pipe is a priority pipe. 
                       Highest priority tasks that are blocked on 
                       this pipe will become unblocked before 
                       lower priority tasks.
                       If both OS_FIFO and OS_PRIORITY are set, 
                       the pipe will be a fifo pipe.
                       The default value for flags is OS_FIFO.
   name                is an optional name for this pipe that is 
                       used for debugging purposes only. Defaults 
                       to null string.
*/

Pipe::Pipe(char* mem, int len, BFlags flags, const char* name) :
	Block(flags, name == 0 ? "Pipe" : name),
	free(len, flags, "Pipe::free"),
	used(0, flags, "Pipe::used"),  pipe(mem)
{
  objType= PipeType;
  pipeLength = len;
  front = back = 0;
}


/* 
Pipe::~Pipe
Description:
   Class Pipe.
   Pipe destructor.
*/

Pipe::~Pipe()
{
}

