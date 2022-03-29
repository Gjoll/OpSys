/*
{inc,copyrite.txt}
*/
/*
  $Revision: 1.1 $
  $Modtime:   12 May 1992 21:34:38  $
  $Workfile:   num2str.cpp  $
*/
#include <IoString.h>
#include <OpSys.h>
#include <debug.h>
#include <compare.h>
static char name[] = __FILE__;
static void testOne(long number)
{
	{
		char testBuf[MAXDIGITS+1];
		char testBuf1[MAXDIGITS+1];
		IOString testStr(testBuf1, sizeof(testBuf1));
		long before = number;
		long after = 0;
		doSprintf("%ld", testBuf, before);
		testStr << flush << testBuf;
		testStr >> dec >> after;
		compare(name, __LINE__, after, before);
	}
	{
		char testBuf[MAXDIGITS+1];
		char testBuf1[MAXDIGITS+1];
		IOString testStr(testBuf1, sizeof(testBuf1));
		int before = (int) number;
		int after = 0;
		doSprintf("%d", testBuf, before);
 		testStr << flush << testBuf;
		testStr >> dec >> after;
		compare(name, __LINE__, after, before);
	}
	{
		char testBuf[MAXDIGITS+1];
		char testBuf1[MAXDIGITS+1];
		IOString testStr(testBuf1, sizeof(testBuf1));
		short before = (short) number;
		short after = 0;
		doSprintf("%d", testBuf, before);
		testStr << flush << testBuf;
		testStr >> dec >> after;
		compare(name, __LINE__, after, before);
	}
}
void num2StrOnce()
{
	testOne(-1l);
	testOne(32768l);
	testOne(-32768l);
	testOne(0x7fffffffl);
	testOne(0x8fffffffl);
	testOne(0x80000000l);
	testOne(0xffffffffl);
}
void num2Str(long start, long stop)
{
	char testBuf[MAXDIGITS+1];
	char testBuf1[MAXDIGITS+1];
	IOString testStr(testBuf, sizeof(testBuf));
	long i = start;
	while (stop--) {
		long lTest = i;
		int iTest = (int) i;
		short sTest = (short) i;
		long lTesta = 0;
		int iTesta = 0;
		short suTesta = 0;
		short sTesta = 0;
		if ((i % 100) == 0)
			Debug::current->spin();
		doSprintf("%d", testBuf1, sTest);
 		testStr << flush << testBuf1 ;
		testStr >> dec >> sTesta;
		compare(name, __LINE__, sTest, sTesta);
		doSprintf("%08d", testBuf1, sTest);
 		testStr << flush << testBuf1 ;
		testStr >> dec >> sTesta;
		compare(name, __LINE__, sTest, sTesta);
		doSprintf("%d", testBuf1, iTest);
		testStr << flush << testBuf1;
		testStr >> dec >> iTesta;
		compare(name, __LINE__, iTest, iTesta);
		doSprintf("%ld", testBuf1, lTest);
		testStr << flush << testBuf1;
		testStr >> dec >> lTesta;
		compare(name, __LINE__, lTest, lTesta);
		doSprintf("%X", testBuf1, sTest);
		testStr << flush << testBuf1;
		testStr >> hex >> suTesta;
		compare(name, __LINE__, sTest, sTesta);
		doSprintf("%o", testBuf1, sTest);
		testStr << flush << testBuf1;
		testStr >> oct >> suTesta;
		compare(name, __LINE__, sTest, sTesta);
		i += 1;
	}
}
