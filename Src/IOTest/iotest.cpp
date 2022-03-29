/*
  $Revision: 1.1 $
  $Modtime:   12 May 1992 21:34:38  $
  $Workfile:   iotest.cpp  $
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

#define STACK_LEN 1024

int swaps;

#ifdef NO_STARTUP_STACK
static MEM stack[20 * 1024]; 
OpSys os(stack, sizeof(stack));
#else
OpSys os(20);
#endif


#ifdef DOS
#include <cdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pcclock.h>
#include <break.h>
inline void ranStart() {randomize();};
inline long ranNum(long num) {return random((int) num);};
PCClock osClock;
CDebug debug;
static USBreak usBreak;
#endif

#ifdef M68302
#include <cdebug.h>
#include <mclock.h>

CDebug debug;
MClock clock;
static long ranInt = 0;
inline void ranStart() {};
inline long ranNum(long num) {return ranInt++ % num;};
#endif

#ifdef SUN
#include <stdlib.h>
#include <cdebug.h>
#include <vclock.h>
#include <sys/types.h>
#include <sys/time.h>
#include <segv.h>
VClock vClock;
CDebug debug;
SegV segV;
inline void ranStart() {srandom((int) time(0));};
inline long ranNum(int num) {return random() % num;};
#endif

static OSTime ticks;
static void startTest()
{
	ticks = os.now();
#ifndef NDEBUG
	swaps = os.swapCount;
#else
        swaps = -1;
#endif
}

static void endTest()
{
#ifndef NDEBUG
	int endswaps = os.swapCount;
#else
        int endswaps = -1;
#endif
	(*Debug::current) << ". Ticks " << dec << os.elapsedTime(ticks)
		<< " Swaps " << dec << (unsigned) (endswaps - swaps)
	<< endl;
}

static void singleTest()
{
	extern cmdIntTestOnce();
	extern void stringTest();
	extern void num2StrOnce();
	extern void cmdSysOnce();
	num2StrOnce();
	stringTest();
	cmdIntTestOnce();
	cmdSysOnce();
}

#define XX_LENGTH 512
static void ranTest()
{
	extern void cmdSubTest();
	extern str2Num(long, long);
	extern num2Str(long, long);
	extern cmdIntTest(int, int);
	startTest();
	long start = ranNum(0x7fffl) * ranNum(0x7ffffl);
	long end = ranNum(XX_LENGTH);
	*Debug::current << "String -> number. Start "
		<< start << " Count " << end << "  ";
	str2Num(start, end);
	endTest();
	startTest();
	start = ranNum(0x7fffl) * ranNum(0x7ffffl);
	end = ranNum(XX_LENGTH);
	*Debug::current << "Number -> String. Start "
		<< start << " Count " << end << "  ";
	num2Str(start, end);
	endTest();
	startTest();
	start = ranNum(0x7fff);
	end = ranNum(XX_LENGTH);
	*Debug::current << "CmdInt Test "
		<< start << " Count " << end << "  ";
	cmdIntTest((int) start, (int) end);
	endTest();
	startTest();
	*Debug::current << "CmdSub Test ";
	cmdSubTest();
	endTest();
}

void testMain(Thread*)
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
	ranStart();
	singleTest();
	while (count-- != 0) 
	  {
	    (*Debug::current) << "** Test " << count << " **" << endl;
	    ranTest();
	  }
	os.exit(-1);
}

Thread testThread(testMain, 4 * STACK_LEN, 0, "Test Thread");
