/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision:   2.1  $
  $Modtime:   01 May 1993 09:34:30  $
  $Workfile:   osconfig.h  $
*/
#ifndef OSCONFIG_H
#define OSCONFIG_H
#define SUN3		/* SUN3 OS4.xx */
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
// The following are time constants. They depend on the clock rate
// used. Set second to the number of clock ticks in a second.
// indicated time interval.
#define SECOND 60
#define TENTH (SECOND/10)
#define HUNDREDTH (SECOND/100)
#define MINUTE (SECOND*60)
#define HOUR (SECOND * 3600)
// VOLATILE
// If the compiler being used supports the VOLATILE keyword, defined this as
// volatile, otherwise define it as nothing.
//#define VOLATILE volatile	/* Compiler supports volatile keyword */
#define VOLATILE		/* Compiler does'nt support volatile keyword */
#define NEAR
#define FAR
#define STACK_GROWS_DOWN 1
extern "C" void exit(int);
inline void exitOpSys(int exitValue)
{
	exit(exitValue);
}
#endif
