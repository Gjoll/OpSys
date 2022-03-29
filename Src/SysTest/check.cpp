/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:28  $
  $Workfile:   check.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <test.h>
#include <debug.h>

void check(int condition, const char* fileName, int lineNumber)
{
	if (!condition) {
		disInts();
		(*Debug::current) << "Test failed File "
			<< fileName
			<< " Line "
			<< lineNumber
			<< "\n";
		os.exit(-4);
	}
}

void check(int* are, int* shouldBe, short length,
		const char* fileName, int lineNumber)
{
	while (length--)
		check(*are++ == *shouldBe++, fileName, lineNumber);
}

