/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/

/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:58  $
  $Workfile:   console.h  $
*/

#ifndef DOSUTIL_H
#define DOSUTIL_S 1

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Pipe.h>
#include <Thread.h>

#define KEY_STACK_LENGTH 2048		// size of stack.

/* 
Console
Description:
   Parent class: Base.
   Class Console implements a keyboard/screen interface with an 
   input and output pipe. The characters typed in via the DOS 
   keyboard will be placed into the input pipe, and the characters 
   read from the output pipe will be printed to the DOS screen.
   2 threads will be started as part of each Console object. One 
   thread will monitor the keyboard, placing any characters found 
   in the input pipe. The other will wait for any characters to be 
   read from the output pipe, and display those. These threads are 
   started from the constructor.
*/

class Console : public Base
{
private:
	Thread inThread;
	Thread outThread;
protected:
public:
	Console(int priority, Pipe* input, Pipe* output);
};



#endif


