/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:38  $
  $Workfile:   blckinfo.cpp  $
*/

#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <OsConfig.h>
#include <Task.h>
#include <OpSys.h>
#include <Block.h>
#include <BitFlag.h>
#include <Semaphore.h>
#include <Pipe.h>
#include <debug.h>
#include <OsTypes.h>
#define TYPE_WIDTH 15
#define NAME_WIDTH 15
#define ADD_WIDTH 8
#define INT_WIDTH 8
#define SHORT_WIDTH 4
#define MINI_WIDTH 2

/* 
OpSys::blockInfo
Description:
   Class OpSys.
   This is a debug routine that prints out information about all 
   currently instantiated blocking objects including all
   Semaphores, BitFlags, and Pipes. The text information
   is written to the debug object. The user must create an object
   derived from class Debug.
*/

static void printHeader(Block* pPtr)
{
  (*Debug::current) << "[" << setw(NAME_WIDTH) << pPtr->name <<
    "] " << setw(ADD_WIDTH) << hex << (long) pPtr << " ";
}

void Semaphore::info()
{
  TaskList* tPtr = blockedList.next;
  printHeader(this);
  (*Debug::current) << setw(SHORT_WIDTH) << value() << "\n";
  while (tPtr != &blockedList)
    {
      (*Debug::current)
	<< "  Task " << setw(NAME_WIDTH) << tPtr->task->name
	  << " Waiting for "
	    << setw(SHORT_WIDTH)
	      << tPtr->task->semaphore.signals
		<< '\n';
      tPtr = tPtr->next;
    }
}

void Pipe::info()
{
  printHeader(this);
  (*Debug::current) << "Used "
    << setw(SHORT_WIDTH)
      << used.value()
	<< " Free "
	  << setw(SHORT_WIDTH)
	    << used.value()
	      << "\n";
  (*Debug::current) << "  Used Elements Semaphore ["
    << setw(NAME_WIDTH)
      << used.name
	<< "]  Address "
	  << setw(ADD_WIDTH)
	    << (long) &used;
  (*Debug::current) << "\n  Free Elements Semaphore ["
    << setw(NAME_WIDTH)
      << free.name
	<< "]  Address "
	  << setw(ADD_WIDTH)
	    << (long) &free
	      << "\n";
}

void BitFlag::info()
{
  TaskList* tPtr = blockedList.next;
  printHeader(this);
  (*Debug::current) << " Bits "
    << setw(4) << value()
      << "\n";
  while (tPtr != &blockedList)
    {
      (*Debug::current) << "  ITask "
	<< setw(15) << tPtr->task->name
	  << " Waiting for Bits " << setw(4)
	    << tPtr->task->bitFlag.bits << "\n";
      tPtr = tPtr->next;
    }
}

void OpSys::blockInfo()
{
  Bool flag;
  static char semaphoreMsg[] =
    "\n Semaphore Name    Address\n";
  static char bitFlagMsg[] =
    "\n BitFlag Name      Address\n";
  static char pipeMsg[] =
    "\n Pipe Name         Address\n";
  Block* pPtr;
  (*Debug::current) << '\n';
  flag = OSFalse;
  for (pPtr = os.blocks.nextBlocks; pPtr != &os.blocks;
       pPtr = pPtr->nextBlocks)
    if (pPtr->objType == SemaphoreType)
      {
	Semaphore* sPtr = (Semaphore*) pPtr;
	if (flag == OSFalse)
	  {
	    (*Debug::current) << semaphoreMsg;
	    flag = OSTrue;
	  }
	sPtr->info();
      }
  flag = OSFalse;
  for (pPtr = os.blocks.nextBlocks; pPtr != &os.blocks;
       pPtr = pPtr->nextBlocks)
    if (pPtr->objType == BitFlagType)
      {
	BitFlag* bPtr = (BitFlag*) pPtr;
	if (flag == OSFalse)
	  {
	    (*Debug::current) << bitFlagMsg;
	    flag = OSTrue;
	  }
	bPtr->info();
      }
  flag = OSFalse;
  for (pPtr = os.blocks.nextBlocks; pPtr != &os.blocks;
       pPtr = pPtr->nextBlocks)
    if (pPtr->objType == PipeType)
      {
	Pipe* p1Ptr = (Pipe*) pPtr;
	if (flag == OSFalse)
	  {
	    (*Debug::current) << pipeMsg;
	    flag = OSTrue;
	  }
	p1Ptr->info();
      }
  (*Debug::current) << "\n";
}

