/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:58  $
  $Workfile:   membuf2.cpp  $
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

/* 
MemBuffer::put
Description:
   Class MemBuffer.
   Put a previously allocated chunk of memory back into free pool. 
   DO NOT put a chunk of memory back that was not allocated via 
   MemBuffer::get!
Parameters:
   mem                 is the memory chunk to free.
   OS_DONE             Operation worked.
   OS_ERROR            Attempt to return a buffer that was not 
                       allocated from this object, or else this 
                       object has been corrupted.
*/

/*
1.	Convert memory pointer into offset into memory array.
2.	Verify that memory chunk was allocated from this memory 
	block. Print error msg if not.
3.	Wait for sole access to object.
4.	Link in memory block being freed into free list at the 
	front. The current front element will now be pointed to 
	by this block, and the pointer to the front element will 
	point to this block.
5.	Signal that there is now one more free block in this objects list.
6.	Allow access to object.
*/

OSRet MemBuffer::put(void* mem)
{ 
  MEM chunk = ((MEM*) mem) - memory;					// 1
  assert(chunk < length * size);					// 2
  if (chunk < length * size)
    {
      access.wait();							// 3
      memory[chunk] = freeList;						// 4
      freeList = chunk;							// 4
      freeCtr.signal(1);						// 5
      access.signal();							// 6
      return OS_DONE;
    }
  return OS_ERROR;
}

