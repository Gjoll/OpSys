/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:28  $
  $Workfile:   Thread.h  $
*/
#ifndef THREAD_H
#define THREAD_H
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <OsTypes.h>
#include <Task.h>

/* 
Thread
Description:
   Parent Class: STask.
   A thread is very similar to a STask. The difference is that a 
   thread is passed a function address in the constructor. That 
   function is started as an independent thread. When that 
   function returns, that thread of execution is stopped.
   Threads always allocate their stack automatically from the 
   original startup stack.
Usage:

   #include <Thread.h>
   #define THREAD_PRIORITY1 (1..255) ???
   #define STACK_SIZE 1024

   extern int iData;
   extern void (*tFcn1)(Thread*, void*);

   Thread thread1(tFcn1, (void*) iData, STACK_SIZE,
			   THREAD_PRIORITY1, "Thread Name");

   #define THREAD_PRIORITY2 (1..255) ???

   extern void (*tFcn2)(Thread*);

   Thread thread1(tFcn2, STACK_SIZE, THREAD_PRIORITY2, "Thread 
		       Name");

Data:
   data                Pointer to a data object to be passed to 
		       the function that is started via this 
		       thread.
   tPtr                Pointer to function to start as separate 
		       thread.
Methods:
   Thread::Thread      Constructor. 2 constructors are provided. 
		       One is for functions that expect a pointer 
		       to a thread and a pointer to void, the 
		       other for starting functions that only 
		       expect a pointer to the thread.
   Thread::run         Task starts thread at this address. This 
		       calls function.
*/

class Thread : public STask
{
 private:
  typedef void (*TPtr)(Thread*, void*);
  typedef void (*TPtr1)(Thread*);
  void* data;
  TPtr tPtr;
 protected:
  void run();
 public:
  Thread(TPtr, void* iData, unsigned int stackLen,
	 short priority, const char* name = 0);
  Thread(TPtr1, unsigned int stackLen,
	 short priority, const char* name = 0);
};

#endif
