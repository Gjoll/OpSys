/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:30  $
  $Workfile:   pipe2.cpp  $
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
Pipe::put2
Description:
   Class Pipe.
   Put character onto the pipe. The calling task will be blocked 
   if not a free byte in the pipe currently, and will become 
   unblocked when a)   the timeout period is up or
   b)  a free bytes is now in pipe.
   The following are the possible return values.
   Value               Meaning
   OS_DONE                 Character was written to the pipe 
                       correctly.
   OS_BLOCKERR         There was not room to put the character 
                       onto the pipe, and the calling task is 
                       marked as unblockable. The character was 
                       not written, the task did not wait for free 
                       space.
   OS_TIMEOUT          There was not room to put the character 
                       onto the pipe, and the calling task timed 
                       out waiting for space to be freed. The 
                       character was not written to the pipe.
   OS_DELETED          There was not room to put the character 
                       onto the pipe, and the Pipe object was 
                       deleted while the calling task was waiting 
                       for space to be freed. The character was 
                       not written to the pipe.
   OS_TOO_LARGE        The character is of a size greater than the 
                       maximum free bytes in the pipe, and can 
                       never be written. The character was, of 
                       course, not written.
Parameters:
   element             is the character to write to the pipe.
   timeout             is the maximum number of clock ticks to 
                       wait for free space in the pipe. Default is 
                       forever.
*/

/*
1. check that Pipe.has been initialized. Debug only.
2. If pipe is not long enough for data element, return.
3. Otherwise wait on used semaphore.
4. If semaphore wait was successful, then copy the character 
   to the pipe circular buffer. Lock out interrupts during copy.
5. Increment used semaphore by 1.
6. Return the semaphore wait status. If there was a wait 
error, tell user that, if it was successful, then OS_DONE will be returned.
*/

OSRet Pipe::put(const char element, OSTime timeout)
{
  OSRet retVal;
  checkInit();								//1
  if (sizeof(char) > pipeLength)					//2
    retVal = OS_TOO_LARGE;
  else if ((retVal = free.wait(1, timeout)) == OS_DONE)			//3
    {
      os.swapOff();							//4
      {
	pipe[back] = element;						//4
	back = back + 1;						//4
	if (back >= pipeLength)						//4
	  back = 0;							//4
      }									//4
      os.swapOn();							//4
      used.signal(1);							//5
    }
  return(retVal);							//6
}

