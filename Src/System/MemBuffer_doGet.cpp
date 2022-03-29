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
  $Workfile:   membuf1.cpp  $
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
MemBuffer::doGet
Description:
   Class MemBuffer.
   This routine is private to MemBuffer. The user should use 
   MemBuffer::get to allocate memory.
   Allocate a chunk of memory from memory block. Optionally 
   specify a timeout period to wait for an available memory chunk. 
   Default timeout period is forever.
   The following are the values that can be returned from 
   MemBuffer::doGet()
   OS_DONE             Operation worked. Memory buffer returned.
   OS_TIMEOUT          The timeout period expired.
   OS_BLOCKERR         No memory blocks are available, and the 
                       calling task is not blockable, and can not 
                       be removed from the active task queue.
   OS_DELETED          The MemBuffer object that the task was 
                       waiting on was deleted.
Parameters:
   mem                 where pointer to allocated memory is 
                       stored.
   timeout             optional maximum period of time (in clock 
                       ticks) to wait for memory block. Default is 
                       forever.
*/

/*
1.	Wait for free block to be available, or timeout to occur. 
	Semaphore keeps count of free blocks.
2.	If not timeout, then there is an available free block.
3.	Get sole access to object.
4.	Get offset in memory to first free chunk on singly linked list.
5.	Set pointer to first free block to second free block.
6.	Allow access to object.
7.	Return address of block just removed from free list.
8.	Return OS_DONE == have block, or reason why we did not 
	get block. See Semaphore::wait() return values.
*/

OSRet MemBuffer::doGet(void** mem, OSTime timeout)
{
  MEM chunk;
  OSRet retVal;
  retVal = freeCtr.wait(1, timeout);					// 1
  if (retVal == OS_DONE) {						// 2
    access.wait();							// 3
    chunk = freeList;							// 4
    freeList = memory[chunk];						// 5
    access.signal();							// 6
    assert(chunk < length * size);
    *mem = &memory[chunk];						// 7
  }
  return retVal;							// 8
}

