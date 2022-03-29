/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:52  $
  $Workfile:   memalc1.cpp  $
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
MemAlloc::get
Description:
   Class MemAlloc.
   Allocate a chunk of memory from memory block.
   The following are the values that can be returned from 
   MemAlloc::get()
   OS_DONE             Operation worked. Memory buffer returned.
   OS_ERROR            The memory allocator object was set up 
                       incorrectly, or was corrupted (probably by 
                       a write off the end of an allocated 
                       buffer). No objects can be gotten from this 
                       object.
   OS_NO_ROOM          No memory of the requested size is 
                       available.
Parameters:
   mem                 where pointer to allocated memory is 
                       stored.
   length              length of request in bytes.
*/

/*
1. If error flag is set, then buffer is corrupt. Return error.
2. Search through free linked list until no more blocks, or find 
   a block large enough.
3. Found a block!
4. Remove block from free list.
5. Block is large enough to split into 2 blocks. Create a second 
   block, link it into free block list and block list. Also remove 
   allocated block from free list.
6. No blocks are available. Return error.
*/

OSRet MemAlloc::get(void** retMem, MEM length)
{
  OSRet retVal;
  length += sizeof(MEM) - 1;
  length /= sizeof(MEM);
  length += HDR_LENGTH;
  if (error == OSTrue)							// 1
    retVal = OS_ERROR;
  else
    {
      MEM chunk = 0;
      MEM cLength;
      access.wait();

      for (;;)
	{								// 2
	  chunk = mem[chunk + NEXT_FREE];
	  if (chunk == 0)
	    break;
	  cLength = mem[chunk + LENGTH];
	  if (cLength >= length)
	    break;
	}

      if (chunk != 0)							// 3
	{
	  unlinkFree(chunk);						// 4
	  retVal = OS_DONE;
	  if (cLength - length > HDR_LENGTH)				// 5
	    {
	      MEM next = chunk + length;
	      {
		MEM tmp = mem[chunk+NEXT];
		mem[next+LAST] = chunk;
		mem[chunk+NEXT] = next;
		mem[next + NEXT] = tmp;
		mem[tmp + LAST] = next;
	      }
	      mem[next+LENGTH] = mem[chunk+LENGTH] -
		length;
	      mem[chunk+LENGTH] = length;
	      linkFree(next);
	    }
	  *retMem = &mem[chunk + HDR_LENGTH];
	  retVal = OS_DONE;
	}
      else
	retVal = OS_NO_ROOM;						// 6
      access.signal();
    }
  return retVal;
}

