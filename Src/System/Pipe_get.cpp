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
  $Workfile:   pipe1.cpp  $
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
Pipe::get2
Description:
   Class Pipe.
   Get an element of arbitrary length from the pipe. Element can
   be from 1 to size of pipe circular buffer long. The calling
   task will be blocked if that many bytes are not in the pipe
   currently, and will become unblocked when
   a)  the timeout period is up or
   b)  the required number of bytes are now in pipe. Blocked tasks 
      will be serviced in the order that they became blocked.
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
                       greater than the maximum used bytes in the 
                       pipe, and can never be read. No data was 
                       read from the pipe.
Parameters:
   element             is where to store the data read from the 
                       pipe.
   count               is the number of bytes data to read from 
                       the pipe.
   timeout             is an optional timeout value specifying the 
                       maximum amount of time that the task should 
                       wait for data to be in the pipe. Default is 
                       forever.
*/

/*
1.	check that Pipe.has been initialized. Debug only.
2.	If number of bytes requested is longer than length of pipe 
circular buffer, return error.
3.	Otherwise wait on used semaphore.
4.	If semaphore wait was successful, then copy the requested 
number of bytes from the pipe circular buffer to the users 
memory. Lock out interrupts during copy.
5.	Increment free semaphore by the number of bytes just 
removed from pipe circular buffer.
6.	Return the semaphore wait status. If there was a wait 
error, tell user that, if it was successful, then OS_DONE will be returned.
*/

OSRet Pipe::get(void* element, int count, OSTime timeout)
{
  OSRet retVal;
  checkInit();								//1
  if (count > pipeLength)						//2
    retVal = OS_TOO_LARGE;
  else if ((retVal = used.wait(count, timeout)) == OS_DONE)		//3
    {									//4
      register char* elemPtr = (char*) element;				//4
      os.swapOff();							//4
      for (int i = count; i > 0; i--)					//4
	{								//4
	  *elemPtr++ = pipe[front];					//4
	  front = front + 1;						//4
	  if (front >= pipeLength)					//4
	    front = 0;							//4
	}
      os.swapOn();
      free.signal(count);						//5
    }
  return(retVal);							//6
}

