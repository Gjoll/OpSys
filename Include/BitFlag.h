/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:32  $
  $Workfile:   BitFlag.h  $
*/
#ifndef BITFLAG_H
#define BITFLAG_H
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>

/* 
BitFlag
Description:
   Parent Class: Block.
   Class BitFlag is used for task synchronization. A task/thread 
   can wait for one or more bits in an object of class BitFlag to 
   be set, or set/clear bits in an object of class BitFlag.
   Any tasks that are waiting for specific bits to be set will be 
   removed from the active task list until the specified bits are 
   set. When the specified condition is fulfilled that task is 
   placed back onto the active task queue.
   A task can wait for one of a set of bits to be set, or it can 
   wait for all in a set of bits to be set. eg wait for bit 4, 6, 
   or 15 to be set OR wait for bit 4, 6, and 15 to be set.
   A task can specify an optional timeout value to be used when 
   waiting for a specific combination of bits. If that condition 
   is not fulfilled within the timeout period, the task is placed 
   back onto the active task.
   The bitflag is initialized with all bits off/clear.
Usage:

   #include <BitFlag.h>
   BitFlag bitFlag("BitFlag Name");

Data:
   bits                The bits in this object that are currently 
		       set/cleared.
Methods:
   BitFlag::BitFlag    Constructor.
   BitFlag::~BitFlag   Destructor.
   BitFlag::info       Print out information about this BitFlag 
		       object to the debug object.
   BitFlag::signal     Set/Clear some bits in BitFlag. Unblocks 
		       any tasks waiting on this object whose wait 
		       conditions are now fulfilled.
   BitFlag::intSignal  Set/Clear some bits in BitFlag. Unblocks
		       any tasks waiting on this object whose wait
		       conditions are now fulfilled. This is callable from an
             interrupt routine. NO TASK RESCHEDULING/SWAPPING IS
             PERFORMED!
   BitFlag::wait       Block current task until the conditions of
		       the wait are fulfilled. That is the bits 
		       specified are set. If the conditions are 
		       met immediately, task is not blocked. An 
		       optional timeout can also be specified to 
		       limit the time that the task waits.
		       The parameter OSWaitBits specifies that the 
		       task should be blocked until all bits 
		       specified are set, or only until one bit of 
		       the bits specified is set.
   BitFlag::value      Return current value of bits.
*/

enum OSWaitBits { OS_ALL, OS_ONE};

class BitFlag : public Block
{
  friend class Test;
 protected:
  unsigned long bits;
 public:
  BitFlag(const char* name = 0);
  ~BitFlag();
  void info();
  OSRet intSignal(unsigned long setBits, unsigned long resetBits);
  OSRet signal(unsigned long setBits, unsigned long resetBits);
  OSRet wait(unsigned long waitBits, OSWaitBits = OS_ALL,
	     OSTime=OS_NOTIMEOUT);
  unsigned long value();
};

/* 
BitFlag::value
Description:
   Class BitFlag.
   Return the current setting of the bitflag bits.
*/
inline unsigned long BitFlag::value()
{
  return(bits);
}
#endif
