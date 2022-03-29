/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:34  $
  $Workfile:   cmdhdr.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <Pipe.h>
#include <IoBuf.h>
#include <CPipe.h>
#include <CmdPipe.h>
#include <CmdHdr.h>
#include <Command.h>

/* 
CmdHdr::CmdHdr
Description:
   Class: CmdHdr.
   Class CmdHdr constructor. This initializes the next and last 
   CmdHdr pointers to itself.
*/

CmdHdr::CmdHdr() 
{
	next = this;
	last = this;
}

/* 
CmdHdr::~CmdHdr
Description:
   Class CmdHdr destructor. Removes the CmdHdr object from
   the CmdHdr linked list.
*/
CmdHdr::~CmdHdr()
{
	next->last = last;
	last->next = next;
	next = this;
	last = this;
};

