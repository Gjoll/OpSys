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
  $Workfile:   Block.h  $
*/
#ifndef BLOCK_H
#define BLOCK_H
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>

/* 
Block
Description:
   Parent class: BlockHdr$.
   Class block is the parent class of all classes that 'block' 
   tasks from active execution (Semaphore, MailBox, Pipe, BitFlag, 
   etc).
   Block objects are used to remove a task from the active task 
   list, and put it onto the 'Blocked' task list until the 
   blocking condition is removed.
Data:
   flags               is a bit flag. The meanings of the bits are 
                       as follows
                       OS_FIFO When this bit is set, then tasks 
                       blocked by Block::blockTask will be 
                       unblocked in FIFO order. When clear tasks 
                       will be unblocked in task priority order.
   nextBlocks          is a pointer to the next element in the 
                       Blocks circular list.
   lastBlocks          is a pointer to the next element in the 
                       Blocks circular list.
   tasks 			   Circular list of tasks blocked on this object.
Methods:
   Block::Block        Constructor.
   Block::~Block       Destructor. Activate all tasks blocked by 
                       this object.
   Block::doUnBlockAll Same as unBlockAll, except does not lock() 
                       and unLock(). Use unBlockAll instead!
   Block::unBlockAll   Remove all tasks that are blocked by this 
                       object and put them onto the active queue.
   Block::linkBlocks     Insert an BlockHdr object after the 
                       BlockHdr object passed.
   Block::unlinkBlocks   Remove an object from Blocks linked 
                       list. Set next and last pointers to itself.
*/

enum BFlags
{
	OS_PRIORITY = 0,	// unblock tasks in priority order.
	OS_FIFO	= 1		// unblock tasks in FIFO order.
};

class Block : public Base
{
 private:
  friend class OpSys;
  friend class Test;
  void doUnBlockAll();
 protected:
  TaskList blockedList;
  Block* nextBlocks;
  Block* lastBlocks;
  BFlags flags;
  OSRet blockTask(OSTime timeout);
 public:
  const char* name;
  
  ObjType objType;
  Block(BFlags bFlags, const char* iName);
  ~Block();
  void unBlockAll();
  void linkBlocks(Block*);
  void unlinkBlocks();
};

/* 
Block::linkBlocks
Description:
   Class Block.
   linkBlocks is used to link an object of type BlockHdr into the 
   Blocks circular list. All objects of type Block are linked into 
   this global list.

*/
inline void Block::linkBlocks(Block* next)
{
  nextBlocks = next;
  lastBlocks = next->lastBlocks;
  next->lastBlocks->nextBlocks = this;
  next->lastBlocks = this;
}


/* 
Block::unlinkBlocks
Description:
      Remove a Task list object instance from 
   Blocked task circular list.
*/

inline void Block::unlinkBlocks()
{
  nextBlocks->lastBlocks = lastBlocks;
  lastBlocks->nextBlocks = nextBlocks;
  nextBlocks = this;
  lastBlocks = this;
}

#endif
