/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:08  $
  $Workfile:   task6.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>

/* 
ITask::stackFree
Description:
   Class ITask.
   Return the number of bytes not used in the stack of this task. 
   Start at unused end of stack and search for part of stack that 
   is not set to the initial value, ie. has been used since task 
   initialization.
   Don't check more than maxUsed bytes. This is put in here for 
   optimization reasons, as checking very large stacks can be time 
   consuming.
   This routine will only return a valid count if the compile time 
   option CHECKSTACK is defined. If it is not, 0 is always 
   returned.
Parameters:
   max                 is the maximum number of bytes in the stack 
                       to check for. This limits the stack check 
                       to some small, reasonable value.
*/

int ITask::stackFree(int max)
{
  int unUsed = 0;
  int stackBytes = stackLen * sizeof(STAK);
#ifdef CHECKSTACK
  unsigned char* stackPtr = (unsigned char*) stack;

  if ((max == -1) && (max > stackBytes))
    max = stackBytes;
  if ((stack == 0) || (stack == (STAKP) -1))
    return(-1);
#ifdef STACK_GROWS_DOWN
  while ((unUsed < max) && (*stackPtr == STACK_CHECK_VALUE))
    {
      unUsed += 1;
      stackPtr += 1;
    }
#else
  stackPtr += unUsed - 1;
  while ((unUsed < max) && (*stackPtr == STACK_CHECK_VALUE))
    {
      unUsed += 1;
      stackPtr -= 1;
    }
#endif
#endif
  return(unUsed);
}

