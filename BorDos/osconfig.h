/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.
*/

/*
  $Revision: 1.1 $
  $Modtime:   12 May 1992 21:35:58  $
  $Workfile:   OsConfig.h  $
*/
#ifndef OSCONFIG_H
#define OSCONFIG_H

// Operating System. Define one of the following for the operating
// system used.
// Alternately, these can be defined in the Makefile, and be left undefined
// here
//#define STAND_ALONE	/* No operating system. */
//#define DOS		/* Dos/OS2 systems. */

//#define MAC		/* Macintosh */
//#define SUN3		/* SUN3 OS4.xx */
// IDLESTACKLEN
// Idle stack length.
#define IDLESTACKLEN	1024

// CHECKSTACK
// If the following is defined, then code is compiled to load the
// stacks with all a5's. This can be used to determine how much of
// the stack has been used, and if any of the stacks have been full,
// or overfull. Compiling with this not defined will speed up the
// construction of tasks.
#define CHECKSTACK	1

// MIN_STACK
// Set this value to the minimum number of bytes that the stack should
// have unused. If fewer than this many bytes are left free, and
// CHECK_STACK is on, then a warning will be issued (when checked).
#define MIN_STACK 64

// VOLATILE
// If the compiler being used supports the VOLATILE keyword, defined this as
// volatile, otherwise define it as nothing.
#define VOLATILE volatile	/* Compiler supports volatile keyword */

// NEAR/FAR
// For dos/OS2, these must be defined as near and far.
#define NEAR near
#define FAR far
		
// STACK_GROWS_DOWN
// STACK_GROWS_DOWN should be set if the stack grows downward
// (eg (sp)--). If the stack grows upwards (stack pointer gets
// larger with each call) then comment STACK_GROWS_DOWN out.
#define STACK_GROWS_DOWN 1
#define SECOND 10

extern "C" void exit(int);

inline void exitOpSys(int exitValue)
{
	exit(exitValue);
}

#endif
