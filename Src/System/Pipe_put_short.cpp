/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:36  $
  $Workfile:   pipe7.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <PtrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <Pipe.h>

/* 
Pipe::put1
Description:
   Class Pipe.
   Put an object of type 'TYPE' onto the pipe. TYPE can be char, 
   short, int, long, or void*.If there is no room in the pipe for 
   the object, then remove the calling task from the active task 
   list until there is room.
   There is an optional timeout period that specifies the maximum 
   number of clock ticks that the task should wait for free space 
   before aborting the write.
   The following are the possible return values.
   Value               Meaning
   OS_DONE             Data element was written to the pipe.
   OS_BLOCKERR         No room to put the data element onto the 
                       pipe, and the calling task is marked as 
                       unblockable. The data was not written, the 
                       task did not wait for free space.
   OS_TIMEOUT          No room to put the data element onto the 
                       pipe, and the calling task timed out 
                       waiting for space to be freed. The data 
                       element was not written to the pipe.
   OS_DELETED          There was not room to put the data element 
                       onto the pipe, and the Pipe object was 
                       deleted while the calling task was waiting 
                       for space to be freed. The data element was 
                       not written to the pipe.
   OS_TOO_LARGE        The data element is of a size greater than 
                       the maximum free bytes in the pipe, and can 
                       never be written. The data object was not 
                       written.
*/
OSRet Pipe::put(const short& element, OSTime timeout)
{
  return(put(&element, sizeof(element), timeout));
}


