/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:24  $
  $Workfile:   test.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <Thread.h>
#include <test.h>

#ifdef NO_STARTUP_STACK
static MEM stack[20 * 1024]; 
OpSys os(stack, sizeof(stack));
#else
OpSys os(20);
#endif

#ifdef DOS
#include <cdebug.h>
#include <stdio.h>
#include <break.h>
#include <pcclock.h>

static USBreak usBreak;
PCClock clock;
CDebug debug;
#endif

#ifdef WIN32
#include <cdebug.h>
#include <w3clock.h>

CDebug debug;
Win3Clock clock;
#endif

#ifdef SUN
#include <cdebug.h>
#include <vclock.h>
#include <segv.h>
extern "C" void sscanf(char*, char*, ...);
VClock clock;
CDebug debug;
SegV segV;
#endif

#ifdef M68302
#include <cdebug.h>
#include <mclock.h>

CDebug debug;
MClock clock;
#endif

static OSTime ticks;
static unsigned int swaps;
static void startTest(const char* startMsg)
{
	(*Debug::current) << startMsg << " " << flush ;
	ticks = os.now();
#ifndef NDEBUG
	swaps = os.swapCount;
#endif
}

static void endTest()
{
	(*Debug::current) << ". Ticks " << os.elapsedTime(ticks)
#ifndef NDEBUG
		<< " Swaps " << (unsigned) (os.swapCount - swaps)
#endif
	<< endl;
}

void Test::doTest()
{
	OSTime checkPoint;
	OSTime deltaTime;
	clock.start();  // should be started, but just in case...
	startTest("Links test");
	links();
	endTest();
	startTest("Swap test");
	ticks = os.now();
	swap();
	endTest();
	startTest("Semaphore test");
	ticks = os.now();
	semaphore1();
	semaphore2();
	endTest();
	startTest("Pipe test");
	ticks = os.now();
	pipe();
	endTest();
	startTest("MailBox test");
	ticks = os.now();
	mailBox();
	endTest();
	startTest("BitFlag test");
	ticks = os.now();
	bitFlag();
	endTest();
	clock.stop();
	startTest("Sleep Test  ");
	checkPoint = os.now();
	sleep1();       Debug::current->spin();
	sleep2();       Debug::current->spin();
	sleep2();       Debug::current->spin();
	sleep4();       Debug::current->spin();
	deltaTime = os.elapsedTime(checkPoint);
	os.tickCount = -1;      sleep2();       Debug::current->spin();
	deltaTime += os.elapsedTime(-1);
	os.tickCount = -10;     sleep2();       Debug::current->spin();
	clock.start();          sleep3();       Debug::current->spin();
	sleep4();
	deltaTime += os.elapsedTime(-10);
	os.tickCount = checkPoint + deltaTime;
	endTest();
	clock.stop();   // real time clock must be disabled !
	checkPoint = os.now();
	startTest("Thread tests");
	thread1();      Debug::current->spin();
	thread2();      Debug::current->spin();
	thread2();      Debug::current->spin();
	deltaTime = os.elapsedTime(checkPoint);
	os.tickCount = -1;
	thread2();      Debug::current->spin();
	deltaTime += os.elapsedTime(-1);
	os.tickCount = -10;
	thread2();      Debug::current->spin();
	deltaTime += os.elapsedTime(-10);
	os.tickCount = checkPoint + deltaTime ;
	endTest();
	clock.start();
	startTest("Memory Block Test");
	tMemBuffer();
	tMemAlloc();
	endTest();
	os.check();
}

void testMain(Thread* thread)
{
	int count = 1;
#ifdef STAND_ALONE
	count = -1;
#else
	int argc = os.argc;
	char** argv = os.argv;
	argv += 1;
	if (argc > 1)
	  sscanf(*argv, "%d", &count);
#endif

	Test test;
	thread->unBlockable();
	while (count-- != 0)
	  {
	    (*Debug::current) << "** Test " << count << " **" << endl;
	    test.doTest();
	  }
	os.exit(-1);
}

Thread testThread(testMain, 5 * STACK_LEN, 0, "Test Thread");
