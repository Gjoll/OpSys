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
  $Workfile:   memalc3.cpp  $
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

void MemAlloc::linkFree(MEM current)
{
  MEM next = mem[NEXT_FREE];
  
  mem[current+NEXT_FREE] = mem[NEXT_FREE];
  mem[current+LAST_FREE] = 0;
  mem[next+LAST_FREE] = current;	
  mem[NEXT_FREE] = current;
}

