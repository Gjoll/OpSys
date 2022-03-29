/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:48  $
  $Workfile:   mailbox1.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <MailBox.h>
 
/* 
MailBox::get
Description:
   Class MailBox.
   Get an element from the MailBox. The calling task will remain 
   blocked until there is an element in the MailBox, or the 
   timeout period expires. After reading the element, the MailBox 
   is marked as empty.
   If a timeout occurs waiting for an element, the operation is 
   aborted.
   The following are the possible return values.
   Value               Meaning
   OS_DONE             Data element was read from the MailBox 
                       correctly.
   OS_BLOCKERR         There was no data element in the MailBox, 
                       and the calling task is marked as 
                       unblockable. No data was read.
   OS_TIMEOUT          There was no data in the MailBox, and the 
                       calling task timed out waiting for data. No 
                       data was read.
   OS_DELETED          The MailBox object was deleted while the 
                       calling task was blocked. No data was read.
Parameters:
   element             is where to store the data read from the 
                       MailBox.
   timeout             is an optional timeout value specifying the 
                       maximum amount of time that the task should 
                       wait for data to be in the MailBox. Default 
                       is forever.
*/

/*
1.	check that MailBox has been initialized. Debug only.
2.	Lock out interrupts for the duration of this function.
3.	If MailBox.has value, mark mailbox as empty and return current 
	value of MailBox.
4.	Otherwise, call Block::blockTask() to remove task from execution 
	until unblocked by timeout expiration or MailBox::put().
5.	Reenable interrupts.
*/

OSRet MailBox::get(long* element, OSTime timeout)
{
  OSRet retVal;
  checkInit();								//1
  os.lock();								//2
  if (full)								//3
    {
      full = OSFalse;
      *element = mailboxVal;
      retVal = OS_DONE;
    } else {
      retVal = blockTask(timeout);					//4
      *element = ((Task*) os.currentTask)->mailbox.response;
    }
  os.unLock();								//8
  return(retVal);
}
