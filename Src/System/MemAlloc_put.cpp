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
  $Workfile:   memalc2.cpp  $
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
MemAlloc::put
Description:
   Class MemAlloc.
   Put a previously allocated chunk of memory back into free pool. 
   DO NOT put a chunk of memory back that was not allocated via 
   MemAlloc::get!
Parameters:
   mem                 is the memory chunk to free.
   OS_DONE             Operation worked.
   OS_ERROR            Attempt to return a buffer that was not 
                       allocated from this object, or else this 
                       object has been corrupted.
*/

#define LAST_FLAG 1
#define NEXT_FLAG 2

OSRet MemAlloc::put(void* retMem)
{ 
  MEM chunk = (MEM) (((MEM*) retMem) - mem);
  chunk -= HDR_LENGTH;
  assert(chunk < memLength);
  if (chunk < memLength )
    {
      access.wait();
      MEM last = mem[chunk + LAST];
      MEM next = mem[chunk + NEXT];
      assert(next < memLength);
      assert(last < memLength);
      short flag = 0;
      if (
	  (next != 0) &&
	  (mem[next + NEXT_FREE] != (MEM) -1)
	  )
	flag += NEXT_FLAG;
      if (
	  (last != 0) &&
	  (mem[last + NEXT_FREE] != (MEM) -1)
	  )
	flag += LAST_FLAG;
      switch (flag)
	{
	case LAST_FLAG + NEXT_FLAG:
	  {
	    MEM nextNext = mem[next + NEXT];
	    mem[last + LENGTH] += mem[chunk + LENGTH] + 
	      mem[next + LENGTH];
	    mem[last + NEXT] = nextNext;
	    mem[nextNext + LAST] = last;
	    unlinkFree(next);
	  }
	  break;
	case NEXT_FLAG:
	  {
	    MEM nextNext = mem[next + NEXT];
	    mem[chunk + LENGTH] += mem[next + LENGTH];
	    mem[chunk + NEXT] = nextNext;
	    mem[nextNext + LAST] = chunk;
	    unlinkFree(next);
	    linkFree(chunk);
	  }
	  break;
	case LAST_FLAG:
	  mem[last + LENGTH] += mem[chunk + LENGTH];
	  mem[last + NEXT] = next;
	  mem[next + LAST] = last;
	  break;
	case 0:
	  linkFree(chunk);
	  break;
	}
      access.signal();
      return OS_DONE;
    }
  return OS_ERROR;
}

