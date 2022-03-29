/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:50  $
  $Workfile:   memalc.cpp  $
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
#include <MemAlloc.h>

/* 
MemAlloc::MemAlloc
Description:
   Class MemAlloc.
   Memory allocator constructor. The user passes a pointer to an 
   array of Mem elements. MemAlloc::MemAlloc will allocate 
   randomly sized chunks of that memory when requested.
Parameters:
   iMemory             iMemory is a pointer to a user defined 
                       external array of Mem elements. This is the 
                       memory that is allocated.
   memLength           is the size of iMemory in bytes.
*/

/*
1. If the amount of memory allocated is not longer than the amount 
   of memory needed to store one block, set error flag and return. No 
   get's will be possible.
2. Set error flag to no errors.
3. Set up circular list header node, containing pointers to next and 
   last elements in list, and next and last free elements in list.
4. Set up first allocatable memory block, containing all the memory 
   that is left.
5. Allow access to this object by incrementing access semaphore.
*/

MemAlloc::MemAlloc(MEM* iMem, MEM iLength) :
access(0, OS_FIFO, "MemAlloc::access"),
mem(iMem),
memLength(iLength / sizeof(MEM))
{
  assert(memLength > 2 * HDR_LENGTH);
  if (memLength <= 2 * HDR_LENGTH)					// 1
    error = OSTrue;
  else
    {
      error = OSFalse;							// 2
      mem[NEXT] = HDR_LENGTH;						// 3
      mem[LAST] = HDR_LENGTH;
      mem[NEXT_FREE] = 0;
      mem[LAST_FREE] = 0;
      mem[LENGTH] = 0;
      mem[HDR_LENGTH + NEXT] = 0;					// 4
      mem[HDR_LENGTH + LAST] = 0;
      mem[HDR_LENGTH + LENGTH] = memLength - HDR_LENGTH;
      linkFree(HDR_LENGTH);
    }
  access.signal(1);							// 5 
}


/* 
MemAlloc::~MemAlloc
Description:
   Memory block destructor.
*/

MemAlloc::~MemAlloc()
{
}

