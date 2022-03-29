/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:22  $
  $Workfile:   ptrBlock.h  $
*/
#ifndef PTRBLOCK_H
#define PTRBLOCK_H
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
/*
OSTime is the variable type used to store clock ticks/times. 
There are special timeout values used when waiting 
for an OpSys object, called OS_NOTIMEOUT and OS_ZEROTIMEOUT.
Their meanings are 
	OS_NOTIMEOUT	No timeout. Wait forever.
	OS_ZEROTIMEOUT	Zero timeout, return immediately.
*/
#define OS_NOTIMEOUT	-1
#define OS_ZEROTIMEOUT	0
typedef long OSTime;
/*
	The following are the possible return values from
	OpSys methods.
*/
enum OSRet
{
	OS_DONE,		// operation complete
	OS_BLOCKERR,		// attempt to block unblockable task
	OS_TIMEOUT,		// block timed out.
	OS_DELETED,		// blocker was deleted
	OS_TOO_LARGE,		// Attempt to put/take more elements
				// off pipe than pipe is long.
	OS_MAILBOX_FULL,	// Attempt to write to full mailbox.
	OS_NO_ROOM,		// no room to perform the desired operation.
	OS_SIZE_ERR,		// MemBuf::get requested size that was
				// too large!
	OS_ERROR		// general error.
};

enum ObjType
{
	PtrBlockType,	// Object if a TaskBlockHdr, TaskHdr, or BlockHdr
	BlockType,	// Object is a generic block type.
	SemaphoreType,	// Object is a semaphore.
	BitFlagType,	// Object is a BitFlag.
	MailBoxType,	// Object is a mailbox.
	PipeType,	// Object is a pipe.
	ITaskType,	// Object is an itask.
	TaskType,	// Object is a Task
	ThreadType	// Object is a thread.
} ;


#endif
