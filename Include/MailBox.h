/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:14  $
  $Workfile:   MailBox.h  $
*/
#ifndef MAILBOX_H
#define MAILBOX_H
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <OsTypes.h>
/* 
MailBox
Description:
   Parent Class: Block.
   An object of class MailBox is one means that tasks have of 
   passing information between themselves. An object of class Task 
   or Thread can send data to a MailBox, or receive data from a 
   MailBox. An object reading data from a MailBox will be blocked 
   until the data is placed onto the MailBox. An object writing 
   data to a MailBox will get an error the mailbox is not empty.
   Optional timeouts can specify how long a task should remain 
   blocked waiting to read data from a MailBox.
   Only objects of type long can be placed onto or removed from a 
   MailBox.
   Tasks blocked on a mailbox can become unblocked in FIFO order, 
   or task priority order (highest priority tasks before lower 
   priority). The user controls this by the flags setting options 
   OS_FIFO, or OS_PRIORITY in the mailbox constructor. Setting the 
   OS_FIFO bit in flags will make this mailbox a FIFO mailbox, and 
   tasks will become unblocked in FIFO order. The task that was 
   blocked first will become unblocked first.
   Setting the OS_PRIORITY bit will make it a priority mailbox. 
   Highest priority tasks will become unblocked before lower 
   priority tasks.
   If both OS_PRIORITY and OS_FIFO are set, then if will be a FIFO 
   mailbox. The default value is OS_FIFO.
Usage:

   #include <MailBox.h>
   MailBox mailBox(OS_FIFO, "MailBoxName");

Data:
   mailBoxVal          Contains current value of mailBox.
   full                Set if mailBoxVal contains a valid value.
Methods:
   MailBox::MailBox    Constructor.
   MailBox::~MailBox   Destructor.
   MailBox::put        Put an element of type long onto the 
                       MailBox.
   MailBox::get        Get an element of type long from the 
                       MailBox. An optional timeout specifies how 
                       long the receiving task will wait for a 
                       used element in the MailBox.
*/

class MailBox : public Block
{
  friend class OpSys;
 protected:
  long mailboxVal;
  Bool full;
 public:
  MailBox(BFlags = OS_FIFO, const char* = 0);
  ~MailBox();
  OSRet put(long element);
  OSRet get(long* element, OSTime=OS_NOTIMEOUT);
};


#endif
