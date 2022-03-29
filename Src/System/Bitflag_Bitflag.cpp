/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:20  $
  $Workfile:   bitflag.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <PtrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <BitFlag.h>

/* 
BitFlag::BitFlag
Description:
   Class BitFlag.
   BitFlag constructor
   Initialize bitflag bits to all off, set name of object, 
   initialize all circular lists, and place object onto Block 
   circular list.
Parameters:
   name                is an optional name to give this object. It 
                       is used for debugging purposes only.
*/

BitFlag::BitFlag(const char* iName) :
	Block(OS_FIFO, iName == 0 ? "BitFlag" : iName)
{
  objType= BitFlagType;
  bits = 0;
}


/* 
BitFlag::~BitFlag
Description:
   Class BitFlag.
   BitFlag destructor.
*/

BitFlag::~BitFlag()
{
}

