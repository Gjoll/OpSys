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
  $Workfile:   mailbox.cpp  $
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
MailBox::MailBox
Description:
   Class MailBox.
   MailBox constructor.
   An optional name for this MailBox can be specified. Parameters:
   flags               is a series of bits that control the action 
                       of this mailbox. The meaning of the flags 
                       are as follow.
                       OS_FIFO - mailbox is a fifo mailbox. Tasks 
                       that are blocked on this mailbox will 
                       become unblocked in FIFO order.
                       OS_PRIORITY - mailbox is a priority 
                       mailbox. Highest priority tasks that are 
                       blocked on this mailbox will become 
                       unblocked before lower priority tasks.
                       If both OS_FIFO and OS_PRIORITY are set, 
                       the mailbox will be a fifo mailbox.
                       The default value for flags is OS_FIFO.
   name                is an optional name for this MailBox that 
                       is used for debugging purposes only. 
                       Defaults to null string.
*/

MailBox::MailBox(BFlags bFlags, const char* name) :
	Block(bFlags, name == 0 ? "MailBox" : name)
{
  objType= MailBoxType;
  full = OSFalse;
}


/* 
MailBox::~MailBox
Description:
   Class MailBox.
   MailBox destructor.
*/

MailBox::~MailBox()
{
}

