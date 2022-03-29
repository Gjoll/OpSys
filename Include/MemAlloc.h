/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:16  $
  $Workfile:   MemAlloc.h  $
*/
#ifndef MEMALLOC_H
#define MEMALLOC_H
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <MemBuffer.h>

/* 
MemAlloc
Description:
   Parent Class: Base.
   The MemAlloc class defines the operations on a memory  buffer 
   that allocate and free chunks of memory.
   The amount of memory allocatable is defined at MemAlloc 
   construction.
Usage:

   #include <MemAlloc.h>

   extern MEM iMemory[MEM_BUFFER_LENGTH];

   MemAlloc MemAlloc(iMemory, sizeof(iMemory), OS_FIFO);

Data:
   memory              Pointer to base of memory available for 
		       allocating.
   length              length of memory buffer in bytes.
   access              Semaphore to restrict access to this object 
		       to one Task at a time.
Methods:
   MemAlloc::MemAlloc  Initialize the memory block.
   MemAlloc::~MemAlloc Destructor.
   MemAlloc::get       Get memory from the MemAlloc.
   MemAlloc::put       Put memory back into the MemAlloc. That 
		       memory is now free to be reallocated via 
		       get.
*/

#define NEXT ((MEM) 0)          /* subscript of next element */
#define LAST ((MEM) 1)          /* subscript of last element */
#define LENGTH ((MEM) 2)        /* length of this chunk. */
#define NEXT_FREE ((MEM) 3)     /* subscript of next free element, -1 */
				/* if current element not free. */
#define LAST_FREE ((MEM) 4)     /* subscript of last free element */
#define HDR_LENGTH ((MEM) 5)    /* length of header in MEM's */

class MemAlloc : public Base
{
  friend class Test;
 private:
  MEM* mem;
  MEM memLength;
  Bool error;
  Semaphore access;
	
  void unlinkFree(MEM);
  void linkFree(MEM);
 protected:
 public:
  MemAlloc(MEM* iMemory, MEM memLength);
  ~MemAlloc();
  OSRet get(void** retPtr, MEM length);
  OSRet put(void*);
};


#endif

