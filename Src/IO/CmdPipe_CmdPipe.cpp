/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:38  $
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
/* 
CmdPipe::CmdPipe
Description:
   Class: CmdPipe.
   CmdPipe constructor.
Parameters:
   mem                 mem is a pointer to a memory buffer that is 
                       used to store pipe data from when it is 
                       written to when it is read. This buffer can 
                       be any size, but should be long enough to 
                       store data without overflowing. After being 
                       linked to the CmdPipe it should not be used 
                       for any other purpose, nor should it be 
                       deleted until after the CmdPipe has been 
                       deleted.
   len                 is the len of mem in bytes.
   flags               is a series of bits that control the action 
                       of this cmdpipe. The meaning of the flags 
                       are as follow.
                       OS_FIFO - cmdpipe is a fifo cmdpipe. Tasks 
                       that are blocked on this cmdpipe will 
                       become unblocked in FIFO order.
                       OS_PRIORITY - cmdpipe is a priority 
                       cmdpipe. Highest priority tasks that are 
                       blocked on this cmdpipe will become 
                       unblocked before lower priority tasks.
                       If both OS_FIFO and OS_PRIORITY are set, 
                       the cmdpipe will be a fifo cmdpipe.
                       The default value for flags is OS_FIFO.
   name                is the name of this cmdpipe. This is the 
                       name that is printed when debug info is 
                       printed out about this cmdpipe. Otherwise 
                       it is not used. If not included defaults to 
                       null string "".
*/
CmdPipe::CmdPipe(char* mem, int len, BFlags flags, const char* name) :
	CPipe(mem, len, flags, name)
{
	inParens = 0;
	outParens = 0;
}

/* 
CmdPipe::~CmdPipe
Description:
   Class: CmdPipe.
   CmdPipe destructor.
*/
CmdPipe::~CmdPipe()
{
}

