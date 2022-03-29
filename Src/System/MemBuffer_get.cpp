/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:00  $
  $Workfile:   membuf3.cpp  $
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
MemBuffer::get
Description:
   Class MemBuffer.
   Get one memory block from MemBuffer. If no Memory buffers are 
   available, block task until one is available, or optional 
   timeout expires. Default timeout is forever.
   If the user requests a chunk of memory that is larger than the 
   fixed size chunks in the MemBuffer, a debug message is printed 
   out if the compile flag NDEBUG is NOT set. The memory will be 
   returned however. For this reason it is VITAL that the user not 
   allocate chunks that are larger then the size of each element 
   of MemBuffer.
   The following are the values that can be returned from 
   MemBuffer::get()
   OS_DONE                 Operation worked. Memory buffer 
                       returned.
   OS_TIMEOUT          The timeout period expired.
   OS_BLOCKERR         No memory blocks are available, and the 
                       calling task is not blockable, and can not 
                       be removed from the active task queue.
   OS_DELETED          The MemBuffer object that the task was 
                       waiting on was deleted.
   OS_SIZE_ERR         The size requested was too large for this 
                       MemBuffer. **mem is undefined!
Parameters:
   mem                 is where the address of the allocated 
                       memory is returned.
   len                 is the amount desired. This must be less 
                       than or equal to chunkLength.
   timeout             is the number of clock ticks to wait for 
                       memory. default is forever.
*/

OSRet MemBuffer::get(void** mem, MEM len, OSTime timeout)
{
  assert(len/sizeof(MEM) <= size);
  if (len/sizeof(MEM) <= size)
    return(doGet(mem, timeout));
  else return OS_SIZE_ERR;
}


