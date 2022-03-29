/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:58  $
  $Workfile:   stask1.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Semaphore.h>
#include <OpSys.h>

/*
STask::allocStack
Description:
   Class STask.
   Allocate a stack for a new task. If no stack can be allocated,
   then return -1 (indicating no stack).
Parameters:
   length              Is the length of the stack in MEM's.
*/

STAKP STask::allocStack(unsigned int length)
{
  void* stack;
  if (os.stackAlloc.get(&stack, length * sizeof(MEM)) != OS_DONE)
    {
      assert(0);
      stack = (void*) -1;
    }
  return (STAKP) stack;
}

