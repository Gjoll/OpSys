/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:32  $
  $Workfile:   pipe3.cpp  $
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
Pipe::put3
Description:
   Class Pipe.
   Put a data element of arbitrary length onto the pipe.
   The calling task will be blocked if count free bytes are not
   in the pipe currently, and will become unblocked when
   a)  the timeout period is up or
   b)  the required number of free bytes are now in pipe. The 
   following are the possible return values.

   Value               Meaning
   OS_DONE             Data element was written to the pipe 
                       correctly.
   OS_BLOCKERR         There was not room to put the data element 
                       onto the pipe, and the calling task is 
                       marked as unblockable. The data was not 
                       written, the task did not wait for free 
                       space.
   OS_TIMEOUT          There was not room to put the data element 
                       onto the pipe, and the calling task timed 
                       out waiting for space to be freed. The data 
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
	error, tell user that, if it was successful, then OS_DONE 
	will be returned.
*/

OSRet Pipe::put(const void* element, int count, OSTime timeout)
{
  OSRet retVal;
  checkInit();								//1
  if (count > pipeLength)						//2
    retVal = OS_TOO_LARGE;
  else if ((retVal = free.wait(count, timeout)) == OS_DONE)		//3
    {
      register char* elemPtr = (char*) element;				//4
      os.swapOff();							//4
      register char* pipePtr = &pipe[back];				//4
      for (int i = count; i > 0; i--)					//4
	{
	  *pipePtr++ = *elemPtr++;					//4
	  back = back + 1;						//4
	  if (back >= pipeLength)
	    {								//4
	      back = 0;							//4
	      pipePtr = pipe;
	    }
	}
      os.swapOn();							//4
      used.signal(count);						//5
    }
  return(retVal);							//6
}
