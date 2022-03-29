/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:22  $
  $Workfile:   pipe10.cpp  $
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
Pipe::putBack1
Description:
   Class Pipe.
   Put an object of type 'TYPE' onto the FRONT of the pipe. This 
   value will be returned by the next Pipe::get call. TYPE can be 
   short, int, or long.If there is no room in the pipe, then 
   return an error.
   The following are the possible return values.
   Value               Meaning
   OS_DONE             Data element was written to the pipe.
   OS_NO_ROOM          There was no room for the data element in 
                       the pipe.
   OS_TOO_LARGE        The data element is of a size greater than 
                       the maximum free bytes in the pipe, and can 
                       never be written. The data object was not 
                       written.
*/
OSRet Pipe::putBack(const char element)
{
  return(putBack(&element, sizeof(element)));
}


