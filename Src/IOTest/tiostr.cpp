/*
{inc,copyrite.txt}
*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1992 08:16:10  $
  $Workfile:   tiostr.cpp  $
*/
#include <IoString.h>
#include <OpSys.h>
#include <debug.h>
#include <compare.h>
static char name[] = __FILE__;
static void stringTest1()
{
	char testBuf[15];
	IOString testStr(testBuf, sizeof(testBuf));
	compare(name, __LINE__, testBuf, "");
	testStr << "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	compare(name, __LINE__, testBuf, "ABCDEFGHIJKLMN");
	for (short i = 0; i < 2; i++) {
		testStr << flush;
		compare(name, __LINE__, testBuf, "");
		testStr << "A";
		compare(name, __LINE__, testBuf, "A");
		testStr << "B";
 		compare(name, __LINE__, testBuf, "AB");
		testStr << "C";
		compare(name, __LINE__, testBuf, "ABC");
		{
			char c[2];
			c[1] = '\0';
			testStr >> c[0];
			compare(name, __LINE__, c, "A");
			testStr >> c[0];
			compare(name, __LINE__, c, "B");
			testStr.putBack('b');
			testStr >> c[0];
			compare(name, __LINE__, c, "b");
			testStr >> c[0];
			compare(name, __LINE__, c, "C");
			testStr >> c[0];
			compare(name, __LINE__, c, "");
		}	
		testStr << "D";
		compare(name, __LINE__, testBuf, "AbCD");
		{
			char c[2];
			c[1] = '\0';
			testStr >> c[0];
			compare(name, __LINE__, c, "D");
		}	
	}
}
static void stringTest2()
{
	char testBuf[15];
	IOString testStr(testBuf, sizeof(testBuf));
	testStr << "  " << setw(5) << "a";
	compare(name, __LINE__, testBuf, "  a    ");
	testStr << "b";
	compare(name, __LINE__, testBuf, "  a    b");
	testStr << "      ";
	compare(name, __LINE__, testBuf, "  a    b      ");
	{
		char c[2];
		c[1] = '\0';
		testStr >> c[0];	
		compare(name, __LINE__, c, " ");
		testStr >> skip(OSTrue) >> c[0];	
		compare(name, __LINE__, c, "a");
		testStr >> skip(OSFalse) >> c[0];	
		compare(name, __LINE__, c, " ");
		testStr >> skip(OSTrue) >> c[0] ;	
		compare(name, __LINE__, c, "b");
	}
}
void stringTest()
{
	stringTest1();
	stringTest2();
}
