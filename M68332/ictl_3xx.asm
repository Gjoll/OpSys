*******************************************************************
* Copyright 1996 Mark J. Giebler.
* This is an unpublished work by Mark J. Giebler. All
* rights are reserved, and no part of this work may be
* distributed or released with out the express permission
* of Mark J. Giebler 23470 Manning Court North, New Scandia, MN  55073-9511
*
*
*	FIle: ictl3xx.src
*	Author: Mark Giebler
*
* This file contains C callable routines to manipulate the CPU32's
* (MC683XX) Vector Base register (VBR) and Status Register (SR)
* These 2 registers are used in interrupt handling.
*
* C callable Trap functions are provided.
*
* NOTE: the 68302 does not have a VBR. (It is fixed at $00000000)
*
	chip  CPU32
	align	2
*
*
* The functions here are used by the module INT_68K.CXX
*
*
*
*
*******************************************************************
*
* extern "C" long get_VBR( void )
*
* returns the contents of the 68332's VBR (Vector Base Register).
*
* CPU must be in supervisor state to execute this function, if not
* an exception trap call will be forced.
*******************************************************************
	XDEF	_get_VBR
_get_VBR
	MOVEC	VBR,D0  * for anything but 68000 use this line of code.
*   MOVE.L  0,D0    * for 68000 only use this line of code.
	RTS
*******************************************************************
*
* extern "C" long set_VBR( long address )
*
* Sets the VBR register to the address provided.
* returns the address that was set as a long.
*
* CPU must be in supervisor state to execute this function, if not
* an exception trap call will be forced.
*
*******************************************************************
	XDEF	_set_VBR
_set_VBR
	MOVE.L	4(SP),D0	* get passed in address
	MOVEC	D0,VBR      * for 68000 remove this line of code.
	RTS
*******************************************************************
*
* extern "C" int setIntLevel( int level )
*
* sets the interrupt disable level.
* 0 - all interrupts on, 7 all of except NMI.
* returns the disable level.
*
* CPU must be in supervisor state to execute this function, if not
* an exception trap call will be forced.
*
*******************************************************************
	XDEF	_setIntLevel
_setIntLevel
	MOVE.W	6(SP),D1
	Move.w	d1,d0
	LSL.W	#8,D0
	ORI.W	#$02000,D0	* KEEP SUPERVISOR STATE ACTIVE.
	MOVE.W	D0,SR
	Move.w	d1,d0
	RTS
********************************************************************
*
* extern "C" int getIntLevel( void )
*
* returns the current disable level for interrupts (0 to 7)
*
********************************************************************
	XDEF	_getIntLevel
_getIntLevel
	Move.w	sr,d0
	lsr.w	#8,d0	* shift level bits down.
	andi.l	#$07,d0	* mask off S bit.
	rts
**********************************************************************
*
* trap0..15
*
* executes trap instruction
*
**********************************************************************
	XDEF	_trap0
_trap0
	trap	#0
	rts
**********************************************************************
*
* trap0..15
*
* executes trap instruction
*
**********************************************************************
	XDEF	_trap1
_trap1
	trap	#1
	rts
**********************************************************************
*
* trap0..15
*
* executes trap instruction
*
**********************************************************************
	XDEF	_trap2
_trap2
	trap	#2
	rts
**********************************************************************
*
* trap0..15
*
* executes trap instruction
*
**********************************************************************
	XDEF	_trap3
_trap3
	trap	#3
	rts
**********************************************************************
*
* trap0..15
*
* executes trap instruction
*
**********************************************************************
	XDEF	_trap4
_trap4
	trap	#4
	rts
**********************************************************************
*
* trap0..15
*
* executes trap instruction
*
**********************************************************************
	XDEF	_trap5
_trap5
	trap	#5
	rts
**********************************************************************
*
* trap0..15
*
* executes trap instruction
*
**********************************************************************
	XDEF	_trap6
_trap6
	trap	#6
	rts
**********************************************************************
*
* trap0..15
*
* executes trap instruction
*
**********************************************************************
	XDEF	_trap7
_trap7
	trap	#7
	rts
**********************************************************************
*
* trap0..15
*
* executes trap instruction
*
**********************************************************************
	XDEF	_trap8
_trap8
	trap	#8
	rts
**********************************************************************
*
* trap0..15
*
* executes trap instruction
*
**********************************************************************
	XDEF	_trap9
_trap9
	trap	#9
	rts
**********************************************************************
*
* trap0..15
*
* executes trap instruction
*
**********************************************************************
	XDEF	_trap10
_trap10
	trap	#10
	rts
**********************************************************************
*
* trap0..15
*
* executes trap instruction
*
**********************************************************************
	XDEF	_trap11
_trap11
	trap	#11
	rts
**********************************************************************
*
* trap0..15
*
* executes trap instruction
*
**********************************************************************
	XDEF	_trap12
_trap12
	trap	#12
	rts
**********************************************************************
*
* trap0..15
*
* executes trap instruction
*
**********************************************************************
	XDEF	_trap13
_trap13
	trap	#13
	rts
**********************************************************************
*
* trap0..15
*
* executes trap instruction
*
**********************************************************************
	XDEF	_trap14
_trap14
	trap	#14
	rts
**********************************************************************
*
* trap0..15
*
* executes trap instruction
*
**********************************************************************
	XDEF	_trap15
_trap15
	trap	#15
	rts
