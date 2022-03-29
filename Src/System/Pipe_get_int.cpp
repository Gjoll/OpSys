/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:26  $
  $Workfile:   pipe14.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <Pipe.h>

/* 
Pipe::get1
Description:
   Class Pipe.
   Get a data element of type 'TYPE' from the pipe. TYPE can be 
   short,
   int, long, char*, or void*. If there are not sizeof(TYPE) bytes 
   in
   the pipe currently, then remove the calling task from the 
   active
   task list until there are.
   There is an optional timeout period that specifies the maximum
   number of clock ticks that the task should wait for data
   before aborting the read.
   The following are the possible return values.
   Value               Meaning
   OS_DONE             Data element was read from the pipe 
                       correctly.
   OS_BLOCKERR         There was no data element in the pipe, and 
                       the calling task is marked as unblockable. 
                       No data was read.
   OS_TIMEOUT          There was no data in the pipe, and the 
                       calling task timed out waiting for data. No 
                       data was read.
   OS_DELETED          There was no data element in the pipe, and 
                       the Pipe object was deleted while the 
                       calling task was waiting for data. No data 
                       was read from the pipe.
   OS_TOO_LARGE        The data element to be read is of a size 
                       greater than the length of the pipe, and 
                       can never be read. No data was read from 
                       the pipe.

*/
OSRet Pipe::get(int* element, OSTime timeout)
{
  return(get(element, sizeof(int), timeout));
}


