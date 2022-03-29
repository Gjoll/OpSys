/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:34  $
  $Workfile:   pipe4.cpp  $
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
Pipe::putBack2
Description:
   Class Pipe.
   Put a data element of arbitrary length onto the front of the 
   pipe. The object is pushed back in reverse order, so that the 
   next Pipe::get call will read it in the correct order.
   The following are the possible return values.

   Value               Meaning
   OS_DONE             Data element was written to the pipe 
                       correctly.
   OS_NO_ROOM          There was no room to put the data back onto 
                       the pipe.
   OS_TOO_LARGE        The data element is of a size greater than 
                       the maximum free bytes in the pipe, and can 
                       never be written. The data object was, of 
                       course, not written.
Parameters:
   element             is a pointer to the data to write to the 
                       pipe.
   count               is the number of bytes of data to write.
   timeout             is an optional timeout value for the 
                       maximum number of clock ticks to wait for 
                       free space in the pipe to write to. Default 
                       is forever.
*/

/*
1.	check that Pipe.has been initialized. Debug only.
2.	If pipe is not long enough for data element, return error.
3.	Otherwise wait on used semaphore.
4.	If semaphore wait was successful, then copy the requested 
	number of bytes from the users memory to the pipe circular buffer.
5.	Increment used semaphore by the number of bytes just put 
	onto the pipe circular buffer.
6.	Return the semaphore wait status. If there was a wait 
	error, tell user that, if it was successful, then OS_DONE will be returned.
*/

OSRet Pipe::putBack(const void* element, int count)
{
  OSRet retVal;
  checkInit();								//1
  if (count > pipeLength)						//2
    retVal = OS_TOO_LARGE;
  else if ((retVal = free.wait(count, OS_ZEROTIMEOUT)) == OS_DONE)	//3
    {
      register char* elemPtr = (char*) element;				//4
      os.swapOff();							//4
      for (int i = count - 1; i >= 0; i--)				//4
	{
	  front = front - 1;						//4
	  if (front < 0)						//4
	    front = pipeLength - 1;					//4
	  pipe[front] = *(elemPtr+i);					//4
	}
      os.swapOn();							//4
      used.signal(count);						//5
    } else if (retVal == OS_TIMEOUT)
      retVal = OS_NO_ROOM;
  return(retVal);							//6
}

