/*
 Copyright (C) Kurt W. Allen 1991
  This file is part of OpSys.
  This program and the information contained in it is proprietary to
  Kurt W. Allen.
  This program is distributed for evaluation purposes only. It may not
  be sold, or distributed as part a commmercial package, without the
  express written permission of Kurt W. Allen.
  Copies may be made and distributed, at no charge, as long as the files are
  unmodified and this copyright notice remains unchanged.
  If this program is usefull, single use copies, and distribution licenses
  can be obtained from

	 Kurt W. Allen
	  3540 43'rd Ave S.
	  Mpls, Mn 55406
	  (612) 722-8799

  This program may not be incorporated in any commercial product of any
  sort, or sold, or distributed in any commercial form with out the
  express written permission of Kurt W. Allen.
  OpSys is distributed without any warranty; without even the implied
  warranty of merchantibility or fitness for a particular purpose.
*/

#include <Task.h>
#include "OpSys.h"

/*
 swap(char* new sp, char** (old sp))
Description:
	Swap one task for another. On entry the stack is as follows.
	sp ->   return address
		address of variable that is to have sp of current task
		sp of task to swap to
		task stack base address
		task stack length
	This routine will save all pertinent registers on the stack of
	the current task, write sp to the variable that will save sp until
	this task is swapped to, reset sp to the new tasks sp, and restore
	all registers from the new stack that were just saved to the old
	stack.
*/

void FAR swap(STAKP FAR* oldSp, STAKP newSp)
{
	asm PUSHA
	asm PUSHF
	asm PUSH DS
	asm PUSH ES

	asm LES BX,oldSp;               	/* *oldSp = current stack pointer */
	asm MOV ES:[BX],SP
	asm MOV ax,ss
	asm MOV ES:2[BX],AX

	asm MOV sp,WORD PTR newSp       	/* Stack pointer = newSp */
	asm MOV SS,WORD PTR newSp+2

	asm POP ES
	asm POP DS
	asm popf;
	asm popa;
}

/*
Function: startTask
Description:
	startTask(long* new stack, long* (old sp))
	start a task for running. Save current tasks registers on the stack,
	store current tasks stack pointer, and set the stack pointer to the
	new stack, and jump to task start address.
	On entry the stack is as follows.
	sp ->   return address
		address of variable that is to have sp of current task
		sp of task to swap to
		task stack base address
		task stack length
*/

void FAR startTask(STAKP FAR *oldSp, STAKP newSp)
{
	asm pusha;
	asm pushf;
	asm PUSH DS;
	asm PUSH ES;

	asm LES BX,oldSp;               /* *oldSp = current stack pointer */
	asm MOV ES:[BX],SP
	asm MOV AX,SS
	asm MOV ES:2[BX],AX

	asm MOV SP,WORD PTR newSp       /* Stack pointer = newSp */
	asm MOV AX,WORD PTR newSp+2
	asm MOV SS,AX

	startTask1();                   /* call startTask1. Will immed.
 					swap back here. */
}

/*
Function: disInts
Description:
	lock out any interrupts that would cause rescheduling to occur.
	eg. enter a critical region.
*/

volatile short disFlag = 0;

void disInts()
{
	disFlag = 1;
}

/*
Function: enInts
Description:
	Enable interrupts disabled by disInts.

*/
void enInts()
{
	disFlag = 0;
}
