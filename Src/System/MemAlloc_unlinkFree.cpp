/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:54  $
  $Workfile:   memalc4.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <MemBuffer.h>
#include <OpSys.h>
#include <MemAlloc.h>

void MemAlloc::unlinkFree(MEM current)
{
  MEM next = mem[current + NEXT_FREE];
  MEM last = mem[current + LAST_FREE];
  
  mem[next+LAST_FREE] = last;	
  mem[last+NEXT_FREE] = next;
  mem[current + LAST_FREE] = (MEM) -1;
  mem[current + NEXT_FREE] = (MEM) -1;
}

