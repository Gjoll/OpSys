/*
{inc,copyrite.txt}
*/
/*
  $Revision: 1.1 $
  $Modtime:   12 May 1992 21:34:38  $
  $Workfile:   str2num.cpp  $
*/
#include <IoString.h>
#include <OpSys.h>
#include <debug.h>
#include <compare.h>
static char name[] = __FILE__;
void str2Num(long start, long stop)
{
	char testBuf[MAXDIGITS+1];
	char test1[MAXDIGITS+1];
	IOString testStr(testBuf, sizeof(testBuf));
	long i = start;
	while (stop--) {
		long lTest = i;
		int iTest = (int) i;
		short sTest = (int) i;
		testStr << setw(0);
		if ((i % 25) == 0)
			Debug::current->spin();
		testStr << flush << dec << sTest;
		compare(name, __LINE__, testBuf, doSprintf("%d", test1, sTest));
		testStr << flush << dec << iTest;
		compare(name, __LINE__, testBuf, doSprintf("%d", test1, iTest));
		testStr << flush << dec << lTest;
		compare(name, __LINE__, testBuf, doSprintf("%ld", test1, lTest));
		testStr << flush << hex << (unsigned) sTest;
		compare(name, __LINE__, testBuf, doSprintf("%X", test1, sTest));
		testStr << flush << oct << (unsigned) sTest;
		compare(name, __LINE__, testBuf, doSprintf("%o", test1, sTest));
		testStr << flush << dec << setw(8) << sTest;
		compare(name, __LINE__, testBuf, doSprintf("%8d", test1, sTest));
		testStr << flush << dec << setw(8) << iTest;
		compare(name, __LINE__, testBuf, doSprintf("%8d", test1, iTest));
		testStr << flush << dec << setw(8) << lTest;
		compare(name, __LINE__, testBuf, doSprintf("%8ld", test1, lTest));
		i += 1;
	}
}
