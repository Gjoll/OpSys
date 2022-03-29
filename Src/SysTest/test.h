/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:32  $
  $Workfile:   test.h  $
*/
#ifndef TEST_H
#define TEST_H

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Thread.h>

#define STACK_LEN 1024

class Test
{
public:
	void doTest();
	void links();
	void block();
	void swap();
	void semaphore1();
	void semaphore2();
	void pipe1();
	void pipe2();
	void pipe3();
	void pipe4();
	void pipe();
	void mailBox1();
	void mailBox2();
	void mailBox();
	void bitFlag();
	void bitFlag1();
	void bitFlag2();
	void bitFlag3();
	void bitFlag4();
	void bitFlag5();
	void sleep1();
	void sleep2();
	void sleep3();
	void sleep4();
	void thread();
	void thread1();
	void thread2();
	void thread2a();
	void thread2b();
	void thread2c();
	void thread2d();
	void thread2e();
	void thread2f();
	void thread2g();
	void thread2h();
	void thread3();
	void tMemBuffer();
	void tMemAlloc();
};

extern void check(int, const char*, int);
extern void check(int*, int*, short, const char*, int);
extern Thread testThread;

#endif
