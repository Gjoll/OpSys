/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:56  $
  $Workfile:   membuf.cpp  $
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
MemBuffer::MemBuffer
Description:
   Class MemBuffer.
   Memory block constructor. The user passes a pointer to an array 
   of Mem elements. MemBuffer::MemBuffer partitions that memory 
   into 'chunkSize' chunks and links them together into a singly 
   linked list. The free semaphore is set to the number of 
   available chunks.
   The number of elements of the Mem array should be defined by 
   the MEMBUFSIZE macro. This macro takes as input the
   number of elements desired in the MemBuffer, and the size of 
   each element ,
   and returns an integer. This integer is the optimal size of the 
   MEM array that the user defines for use by the MemBuffer. This 
   size will insure that the user defined memory buffer is exactly 
   the right length. See usage below.
Parameters:
   iMemory             iMemory is a pointer to a user defined 
                       external array of Mem elements. This is the 
                       memory that is partitioned. The size of 
                       this memory block determines how many 
                       memory chunks can be allocated.
   memLength           is the size of iMemory in bytes.
   chunkSize           is the size of each memory chunk allocated 
                       from iMemory.
   flags               is a series of bits that control the action 
                       of this MemBuffer. The meaning of the flags 
                       are as follow.
                       OS_FIFO - MemBuffer is a fifo MemBuffer. 
                       Tasks that are blocked on this MemBuffer 
                       will become unblocked in FIFO order.
                       OS_PRIORITY - MemBuffer is a priority 
                       MemBuffer. Highest priority tasks that are 
                       blocked on this MemBuffer will become 
                       unblocked before lower priority tasks.
                       If both OS_FIFO and OS_PRIORITY are set, 
                       the MemBuffer will be a fifo MemBuffer.
                       The default value for flags is OS_FIFO.
   for debugging purposes only.
*/

MemBuffer::MemBuffer(MEM* mem, MEM len, MEM siz,BFlags flags) :
	freeCtr(0, flags, "MemBuffer::free"),
	access(0, flags, "MemBuffer::access"),
	memory(mem),
	size((siz + sizeof(MEM) - 1) / sizeof(MEM)),
	length(len/(size * sizeof(MEM)))
{
  // Verify that Memory area size is integer multiple of chunk size
  assert(length * size * sizeof(MEM) == len);
  assert(len >= siz);
  freeList = 0;
  MEM i = 0;
  for (i = 0; i < length * size; i += size)
    memory[i] = i + size;
  memory[i - size] = (MEM) -1;
  freeCtr.signal(length);
  access.signal(1); 
}


/* 
MemBuffer::~MemBuffer
Description:
   Memory block destructor.
*/

MemBuffer::~MemBuffer()
{
}

