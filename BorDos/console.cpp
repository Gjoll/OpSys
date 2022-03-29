/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/

/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:54  $
  $Workfile:   console.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <MemBuffer.h>
#include <OpSys.h>
#include <Pipe.h>
#include <Thread.h>
#include <IoBuf.h>
#include <CPipe.h>
#include <console.h>
#include <debug.h>
#include <conio.h>

/* 
Console::Console
Description:
   Class: Console.
   Console constructor. This starts the input and output threads.
*/

static void input(Thread* me, void* in)
{
	Pipe* inPipe = (Pipe*) in;

	while (1) {
		os.swapOff();
		while (kbhit()) {
			char c = getch();
			*Debug::current << c;
			inPipe->put(c);
		}
		os.swapOn();
		me->sleep(SECOND / 10);
	}
}

static void output(Thread*, void* out)
{
	Pipe* outPipe = (Pipe*) out;
	while (1)
	{
		char c;
		outPipe->get(&c);
		*Debug::current << c;
	}
}

Console::Console(int priority, Pipe* inPipe, Pipe* outPipe) :
	inThread(input, inPipe, KEY_STACK_LENGTH,
		priority, "InThread"),
	outThread(output, outPipe, KEY_STACK_LENGTH,
		priority, "OutThread")
{
}



