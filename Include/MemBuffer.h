/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:18  $
  $Workfile:   MemBuf.h  $
*/
#ifndef MEMBUFFER_H
#define MEMBUFFER_H
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>

/* 
MemBuffer
Description:
   Parent Class: Base.
   The MemBuffer class defines the operations on a memory  buffer 
   that allocate and free fixed size chunks of memory.
   The size of a memory chunk, and the number of chunks 
   allocatable are defined at MemBuffer construction.
   To optimize the size of the memory buffers that the user 
   defines, the user should use the MEMBUFSIZE macro. This macro 
   takes as input the
   number of elements desired in the MemBuffer, and the size of 
   each element ,
   and returns an integer. This integer is the optimal size of the 
   MEM array that the user defines for use by the MemBuffer. This 
   size will insure that the user defined memory buffer is exactly 
   the right length. See usage below.
   Tasks blocked on a MemBuffer can become unblocked in FIFO 
   order, or task priority order (highest priority tasks before 
   lower priority). The user controls this by the flags setting 
   options OS_FIFO, or OS_PRIORITY in the MemBuffer constructor. 
   Setting the OS_FIFO bit in flags will make this MemBuffer a 
   FIFO MemBuffer, and tasks will become unblocked in FIFO order. 
   The task that was blocked first will become unblocked first.
   Setting the OS_PRIORITY bit will make it a priority MemBuffer. 
   Highest priority tasks will become unblocked before lower 
   priority tasks.
   If both OS_PRIORITY and OS_FIFO are set, then if will be a FIFO 
   MemBuffer. The default value is OS_FIFO.
Usage:

   #include <MemBuf.h>

   #define ELEMENTS ???
   #define SIZE ???
   #define MEM_BUFFER_LENGTH MEMBUFSIZE(ELEMENTS, SIZE)

   extern MEM iMemory[MEM_BUFFER_LENGTH];
   MemBuffer memBuffer(iMemory, sizeof(iMemory), SIZE, OS_FIFO);

Data:
   freeCtr             FreeCtr is a counting semaphore set to the 
		       total number of free memory blocks 
		       available.
   memory              Pointer to base of memory available for 
		       allocating.
   length              # of 'size' chunks in *memory (see size 
		       below).
   size                Size of each allocated memory chunk.
   access              Semaphore to restrict access to this object 
		       to one Task at a time.
Methods:
   MemBuffer::MemBuffer    Initialize the memory block.
   MemBuffer::~MemBuffer   Destructor.
   MemBuffer::get      Get 1 chunk of memory from the MemBuffer. 
		       There is an optional timeout waiting for a 
		       free block to be available.
   MemBuffer::info     Print out information about this object to 
		       the debug output pipe.
   MemBuffer::put      Put 1 chunk back into the MemBuffer. That 
		       chunk is now free to be reallocated via 
		       get.
   MemBuffer::value    Return number of chunks currently available 
		       for allocation.
*/

#define MEMBUFSIZE(elements, size) \
		(elements * ((size + sizeof(MEM) - 1)/ \
		sizeof(MEM)))
class MemBuffer : public Base
{
  friend class Test;
 private:
  Semaphore freeCtr;
  Semaphore access;
  MEM freeList;
  MEM* const memory;
  const MEM size;
  const MEM length;
 protected:
  OSRet doGet(void** retPtr, OSTime);
 public:
  MemBuffer(MEM* iMemory, MEM memLength,
	    MEM chunkSize, BFlags = OS_FIFO);
  ~MemBuffer();
  OSRet get(void** retPtr, MEM length,
	    OSTime=OS_NOTIMEOUT);
  void info();
  OSRet put(void*);
  MEM value();
};

/* 
MemBuffer::value
Description:
   Class MemBuffer.
   Return number of free blocks available for allocation.
*/
inline MEM MemBuffer::value()
{
  return freeCtr.value();
}

#endif
