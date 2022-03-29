/*
 (c) Kurt W. Allen 1990
 Created in 1990 as an unpublished copyright work. This
 program and the information contained in it is confidential
 and proprietary to Kurt W. Allen and may not be used, copied, or repro-
 duced without the prior written permission of Kurt W. Allen.
*/
#include <sun4/trap.h>
/*
 void swap();
 Swap one task for another.
 This routine will save all pertinant registers on the stack of the
 current task, write sp to the variable that will save sp until
 this task is swapped to, reset sp to the new tasks sp, and restore
 all registers from the new stack that were just saved to the old stack.
 On entry the external global variable curSp points to the variable to store
 the current stack pointer into, and newSp contains the new stack pointer.
*/
extern long** curSp;
extern long* newSp;
void swap()
{
	asm("ta 3");				/* flush windows */
	asm("sethi %hi(_curSp),%o0");
	asm("ld [%o0+%lo(_curSp)],%o0");
	asm("st %sp,[%o0]");
	asm("sethi %hi(_newSp),%o0");
	asm("ld [%o0+%lo(_newSp)],%sp");
}
/*
 startTask()
 start a task for running. Save current tasks registers on the stack,
 store current tasks stack pointer, and set the stack pointer to the
 new stack, and jump to task start address.
 On entry the external global variable curSp points to the variable to store
 the current stack pointer into, and newSp contains the new stack pointer.
*/
extern startTask1__Fv();
startTask()
{
	asm("ta 3");				/* clean windows */
	asm("sethi %hi(_curSp),%o0");
	asm("ld [%o0+%lo(_curSp)],%o0");
	asm("st %sp,[%o0]");
	asm("sethi %hi(_newSp),%o0");
	asm("ld [%o0+%lo(_newSp)],%sp");
	asm("mov 0,%fp");
	startTask1__Fv();
}
