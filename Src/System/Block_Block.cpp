/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:40  $
  $Workfile:   block.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>

/* 
   Block::Block
   Description:
   Class Block.
   Block constructor.
   This will link the object into the Block list. All objects of 
   class block are linked into this list. It also sets the object 
   Class and name of the block.
   Parameters:
   name                is an optional ASCII name to give this 
   object for debugging purposes.
   */

Block::Block(BFlags iFlags, const char* iName) :
flags(iFlags),
blockedList(0)
{
  nextBlocks = this;
  lastBlocks = this;
  name = iName;
  objType= BlockType;
  os.lock();
  linkBlocks(&os.blocks);
  os.unLock();
}


/* 
Block::~Block
Description:
   Class Block.
   Block destructor.
   Unblock all tasks blocked by this object, and remove this 
   object from the Block list.
*/

Block::~Block() 
{
  unBlockAll();
  os.lock();
  unlinkBlocks();
  os.unLock();
  assert(nextBlocks == this);
  assert(lastBlocks == this);
}
