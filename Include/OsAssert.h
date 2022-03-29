/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:30  $
  $Workfile:   assert.h  $
*/
#ifndef OSASSERT_H
#define OSASSERT_H
/* 
assert
Description:
   The assert macro is used during debugging to verify
   that some condition is
   true. If that condition is not true, an error message is
   printed specifying the source file in which the error
   occurred
   and the line number in the source file where the
   assertion is
   located. This is used to verify that those things that
   are assumed to have happened, actually happened.
   Asserts compile into a run time check of the condition only
   if the compile flag NDEBUG is not defined.
   If it is defined,
   asserts compile to nothing, and no run time checking is
   performed.
   For assert()'s to function,  The user must create an object 
   derived
   from class Debug.
*/

#ifdef NDEBUG
#define assert(cond)
#else
#define assert(cond) if (!(cond)) Assert(__FILE__, __LINE__);
extern void Assert(const char* fileName, int line);
#endif /* NDEBUG */


#endif /* ASSERT_H */
