/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:50  $
  $Workfile:   cpipe.cpp  $
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

/* 
CPipe::CPipe
Description:
   Class: CPipe.
   CPipe constructor.
Parameters:
   mem                 is the external, user defined, character 
                       buffer used by the cpipe for storing data 
                       from when it is written to the cpipe until 
                       it is read.
   length              is the length of mem in bytes 
                       (sizeof(*mem)).
   flags               is a series of bits that control the action 
                       of this cpipe. The meaning of the flags are 
                       as follow.
                       OS_FIFO - cpipe is a fifo cpipe. Tasks that 
                       are blocked on this cpipe will become 
                       unblocked in FIFO order.
                       OS_PRIORITY - cpipe is a priority cpipe. 
                       Highest priority tasks that are blocked on 
                       this cpipe will become unblocked before 
                       lower priority tasks.
                       If both OS_FIFO and OS_PRIORITY are set, 
                       the cpipe will be a fifo cpipe.
                       The default value for flags is OS_FIFO.
   name                is the name given this cpipe for debugging 
                       purposes. If none given, defaults to null 
                       string.
*/

CPipe::CPipe(char* mem, int length, BFlags flags, const char* name) :
	Pipe(mem, length, flags, name), IOBuf()
{
}


/* 
CPipe::~CPipe
Description:
   Class: CPipe.
   CPipe destructor.
*/

CPipe::~CPipe()
{
}

