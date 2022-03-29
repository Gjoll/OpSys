/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:50  $
  $Workfile:   mailbox2.cpp  $
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
MailBox::put
Description:
   Class MailBox.
   Put an element onto the MailBox. If any tasks are currently 
   blocked waiting for data to read from the mailbox, the next 
   task waiting will become unblocked and get the value of the 
   mailbox. If no tasks are currently waiting, the next 
   MailBox::get call will return the value just set.
   It is an error (OS_MAILBOX_FULL) to write to a mailbox that is 
   full already.
   The following are the possible return values.
   Value               Meaning
   OS_DONE             Data element was written to the MailBox 
                       correctly.
   OS_MAILBOX_FULL     Mailbox has a data element in it currently, 
                       and can not be written to until a 
                       MailBox::get call has been made.
Parameters:
   element             is the character to write to the MailBox.
*/

/*
1.	check that MailBox.has been initialized. Debug only.
2.	Lock out interrupts.
3.	If mailbox is full, return error.
4.	Otherwise. if there are any tasks currently blocked waiting 
	to read from the mailbox, unblock them and send the mailbox 
	value to them, and reschedule tasks.
5.	Otherwise, mark mailbox as full and store mailbox value for 
	next MailBox::get() call.
6.	Reenable interrupts.
*/

OSRet MailBox::put(long element)
{
  OSRet retVal = OS_DONE;
  checkInit();								// 1
  os.lock();								// 2

  if (full == OSTrue)							// 3
    retVal = OS_MAILBOX_FULL;
  else
    {
      if (blockedList.next != &blockedList)				// 4
	{
	  register ITask* ptr = blockedList.next->task;

	  ptr->blockReturn = OS_DONE;
	  ptr->mailbox.response = element;
	  ptr->blockedList.unlink();
	  ptr->timeList.unlink();
	  ptr->activate();
	  os.doSchedule();
	}
      else
	{								//5
	  full = OSTrue;
	  mailboxVal = element;
	}
    }
  os.unLock();								//6
  return(retVal);
}

