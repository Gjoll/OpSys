/*
  (c) Kurt W. Allen 1990
  Created in 1990 as an unpublished copyright work. This
  program and the information contained in it is confidential
  and proprietary to Kurt W. Allen and may not be used, copied, or repro-
  duced without the prior written permission of Kurt W. Allen.
  */
extern long** curSp;
extern long* newSp;
/*
  swap()
  Swap one task for another. On entry, the global variable curSp points
  to the variable that shoudl hold the current stack pointer, and newSp
  contains the new stack pointer value.
  This routine will save all pertinant registers on the stack of the
  current task, write sp to the variable that will save sp until
  this task is swapped to, reset sp to the new tasks sp, and restore
  all registers from the new stack that were just saved to the old stack.
  1. Save current register values onto the current stack.
  2. Get pointer to long integer to save current stack pointer into.
  3. Store current stack pointer.
  4. Get new stack pointer.
  5. Restore registers of new task.
  */
swap()
{
									/*1*/
	asm("moveml	d0/d1/d2/d3/d4/d5/d6/d7/a0/a1/a2/a3/a4/a5/a6,sp@-");
	asm("movel _curSp, a0");					/*2*/
	asm("movel sp, a0@");						/*3*/
	asm("movel _newSp, sp");					/*4*/
									/*5*/
	asm("moveml sp@+, d0/d1/d2/d3/d4/d5/d6/d7/a0/a1/a2/a3/a4/a5/a6");
}
/*
 startTask(long* new stack, long* (old sp))
 start a task for running. Save current tasks registers on the stack,
 store current tasks stack pointer, and set the stack pointer to the
 new stack, and jump to task start address.
 On entry, the global variable curSp points to the variable that should
 hold the current stack pointer, and newSp contains the new stack pointer
 value.
 1. Save current tasks registers on the stack.
 2,3. Save current stack pointer.
 4. Set stack pointer into new stack.
 5. Jump to task start routine.
 6. Should never return.
*/
startTask()
{
	asm("moveml d0/d1/d2/d3/d4/d5/d6/d7/a0/a1/a2/a3/a4/a5/a6,sp@-");/*1*/
	asm("movel _curSp, a0");					/*2*/
	asm("movel sp, a0@");					     	/*3*/
	asm("movel _newSp, sp");					/*4*/
	asm("jmp _startTask1__Fv");					/*5*/
}

