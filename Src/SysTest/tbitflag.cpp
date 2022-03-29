/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:24  $
  $Workfile:   tbitflag.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <BitFlag.h>
#include <test.h>

class BTask : public STask
{
	BitFlag *wait;
	int* counter;
	long bits;
	OSWaitBits type;
public:
	BTask(short priority, const char* const name,
		BitFlag* wait, OSWaitBits type, long iBits, int* counter);
	~BTask() {};
	void run();
};

BTask::BTask(short priority, const char* const name,
		BitFlag* iWait, OSWaitBits iType, long iBits, int* iCounter) :
		STask(STACK_LEN, priority, name)
{
	wait = iWait;
	type = iType;
	bits = iBits;
	counter = iCounter;
	start();
};

void BTask::run()
{
	check(wait->wait(bits, type) == OS_DONE, __FILE__, __LINE__);
	*counter += 1;
}

void Test::bitFlag()
{
	bitFlag1();
	bitFlag2();
	bitFlag3();
	bitFlag4();
	bitFlag5();
}

void Test::bitFlag1()
{
	int counter[3];
	counter[0] = 0;
	counter[1] = 0;
	counter[2] = 0;
	BitFlag b1("b1");
	static int vals[] = {0,0,0};
	static int vals1[] = {1,1,0};
	os.check();
	check(b1.wait(1, OS_ONE) == OS_BLOCKERR, __FILE__, __LINE__);
	BTask t1(1, "t1", &b1, OS_ONE, 0x1, counter);
	BTask t2(2, "t2", &b1, OS_ONE, 0x7, counter+1);
	BTask t3(3, "t3", &b1, OS_ONE, 0x8000, counter+2);
	os.check();
	check(b1.value() == 0, __FILE__, __LINE__);
	check(b1.signal(0, 0xffffffffl) == OS_DONE, __FILE__, __LINE__);
	os.check();
	check(b1.value() == 0, __FILE__, __LINE__);
	check(counter, vals, elementsof(vals), __FILE__, __LINE__);
	
	check(b1.signal(1, ~1) == OS_DONE, __FILE__, __LINE__);
	os.check();
	check(b1.value() == 1, __FILE__, __LINE__);
	check(counter, vals1, elementsof(vals1), __FILE__, __LINE__);
}

void Test::bitFlag2()
{
	static int vals[] = {0,1,0};
	int counter[3];
	counter[0] = 0;
	counter[1] = 0;
	counter[2] = 0;
	BitFlag b1("b1");
	BTask t1(1, "t1", &b1, OS_ONE, 0x1, counter);
	BTask t2(2, "t2", &b1, OS_ONE, 0x7, counter+1);
	BTask t3(3, "t3", &b1, OS_ONE, 0x8000, counter+2);
	os.check();
	check(b1.signal(4, 0) == OS_DONE, __FILE__, __LINE__);
	os.check();
	check(b1.value() == 4, __FILE__, __LINE__);
	check(counter, vals, elementsof(vals),__FILE__, __LINE__);
}

void Test::bitFlag3()
{
	static int vals[] = {0,0,1};
	int counter[3];
	counter[0] = 0;
	counter[1] = 0;
	counter[2] = 0;
	BitFlag b1("b1");
	BTask t1(1, "t1", &b1, OS_ONE, 0x1, counter);
	BTask t2(2, "t2", &b1, OS_ONE, 0x7, counter+1);
	BTask t3(3, "t3", &b1, OS_ONE, 0x8000, counter+2);
	os.check();
	check(b1.signal(0x8000, 0) == OS_DONE, __FILE__, __LINE__);
	os.check();
	check(b1.value() == 0x8000, __FILE__, __LINE__);
	check(counter, vals, elementsof(vals),__FILE__, __LINE__);
}

void Test::bitFlag4()
{
	static int vals[] = {0,0,0};
	static int vals1[] = {1,0,0};
	static int vals2[] = {1,0,1};
	static int vals3[] = {1,1,1};
	int counter[3];
	counter[0] = 0;
	counter[1] = 0;
	counter[2] = 0;
	BitFlag b1("b1");
	BTask t1(1, "t1", &b1, OS_ALL, 0x1, counter);
	BTask t2(2, "t2", &b1, OS_ALL, 0x7, counter+1);
	BTask t3(3, "t3", &b1, OS_ALL, 0x8000, counter+2);
	os.check();
	check(b1.signal(0x4, 0) == OS_DONE, __FILE__, __LINE__);
	os.check();
	check(b1.value() == 4, __FILE__, __LINE__);
	check(counter, vals, elementsof(vals),__FILE__, __LINE__);
	check(b1.signal(0x1, 0) == OS_DONE, __FILE__, __LINE__);
	os.check();
	check(b1.value() == 5, __FILE__, __LINE__);
	check(counter, vals1, elementsof(vals1),__FILE__, __LINE__);
	check(b1.signal(0x8000, 0) == OS_DONE, __FILE__, __LINE__);
	os.check();
	check(b1.value() == 0x8005, __FILE__, __LINE__);
	check(counter, vals2, elementsof(vals2),__FILE__, __LINE__);
	check(b1.signal(0x7, 0) == OS_DONE, __FILE__, __LINE__);
	os.check();
	check(b1.value() == 0x8007, __FILE__, __LINE__);
	check(counter, vals3, elementsof(vals3),__FILE__, __LINE__);
}

void Test::bitFlag5()
{
	static int vals[] = {1,1,0};
	static int vals1[] = {1,1,0};
	static int vals2[] = {1,1,1};
	int counter[3];
	counter[0] = 0;
	counter[1] = 0;
	counter[2] = 0;
	BitFlag b1("b1");
	BTask t1(1, "t1", &b1, OS_ALL, 0x1, counter);
	BTask t2(2, "t2", &b1, OS_ALL, 0x7, counter+1);
	BTask t3(3, "t3", &b1, OS_ALL, 0x8001, counter+2);
	os.check();
	check(b1.signal(0x7, 0) == OS_DONE, __FILE__, __LINE__);
	os.check();
	check(b1.value() == 0x7, __FILE__, __LINE__);
	check(counter, vals, elementsof(vals), __FILE__, __LINE__);
	check(b1.signal(0x8000, 1) == OS_DONE, __FILE__, __LINE__);
	os.check();
	check(b1.value() == 0x8006, __FILE__, __LINE__);
	check(counter, vals1, elementsof(vals1), __FILE__, __LINE__);
	check(b1.signal(0x1, 0) == OS_DONE, __FILE__, __LINE__);
	os.check();
	check(b1.value() == 0x8007, __FILE__, __LINE__);
	check(counter, vals2, elementsof(vals2), __FILE__, __LINE__);
}
 
