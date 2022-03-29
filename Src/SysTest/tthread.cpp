/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:28  $
  $Workfile:   tthread.cpp  $
*/
const char fileName[] = __FILE__;
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <BitFlag.h>
#include <Pipe.h>
#include <Thread.h>
#include <test.h>
#include <clock.h>
#include <debug.h>

class TStruct
{
public:
	short value;
	OSTime time;
	TStruct(OSTime t);
};

TStruct::TStruct(OSTime t)
{
        value = 0;
        time=t;
};

void run(Thread* thread, void* sPtr)
{
	TStruct* ssPtr = (TStruct*) sPtr;
	thread->sleep(ssPtr->time);
	ssPtr->value += 1;
}
static TStruct one(10);
static TStruct two(5);
static TStruct three(15);
static TStruct four(17);
static TStruct five(7);
static TStruct six(3);
static TStruct seven(16);
static void check7(short t1, short t2, short t3, short t4, short t5,
	short t6, short t7, short line)
{
	check(one.value == t1, fileName, line);
	check(two.value == t2, fileName, line);
	check(three.value == t3, fileName, line);
	check(four.value == t4, fileName, line);
	check(five.value == t5, fileName, line);
	check(six.value == t6, fileName, line);
	check(seven.value == t7, fileName, line);
}
void Test::thread1()
{
	one = TStruct(1);
 	os.check();
	Thread t1(run, &one, STACK_LEN, 1);
 	os.check();
	check(os.timeList.next->task == &t1, fileName, __LINE__);
	check(t1.timeList.next == &os.timeList, fileName, __LINE__);
	os.swapOff();
	os.clockTick();		// task should become unblocked after
				// one clock tick
	os.swapOn();
	os.check();
	check(os.timeList.next == &os.timeList, fileName, __LINE__);
	check(t1.timeList.next->task == &t1, fileName, __LINE__);
	check(one.value == 0, fileName, __LINE__);
	os.schedule();				// start task t1?
	check(one.value == 1, fileName, __LINE__);	// did task run?
}
void Test::thread2()
{
	one = TStruct(10);
	two = TStruct(5);
	three = TStruct(15);
	four = TStruct(17);
	five = TStruct(7);
	six = TStruct(3);
	seven = TStruct(16);
 	os.check();
	Thread t1(run, &one, STACK_LEN, 10);
 	os.check();
	Thread t2(run, &two, STACK_LEN, 10);
 	os.check();
	Thread t3(run, &three, STACK_LEN, 10);
 	os.check();
	Thread t4(run, &four, STACK_LEN, 10);
 	os.check();
	Thread t5(run, &five, STACK_LEN, 10);
 	os.check();
	Thread t6(run, &six, STACK_LEN, 10);
 	os.check();
	Thread t7(run, &seven, STACK_LEN, 10);
 	os.check();
	check(os.timeList.next->task == &t6, fileName, __LINE__);
	check(t1.timeList.next->task == &t3, fileName, __LINE__);
	check(t2.timeList.next->task == &t5, fileName, __LINE__);
	check(t3.timeList.next->task == &t7, fileName, __LINE__);
	check(t4.timeList.next == &os.timeList, fileName, __LINE__);
	check(t5.timeList.next->task == &t1, fileName, __LINE__);
	check(t6.timeList.next->task == &t2, fileName, __LINE__);
	check(t7.timeList.next->task == &t4, fileName, __LINE__);
	os.clockTick();	os.clockTick();	
	os.schedule();
	check7(0, 0, 0, 0, 0, 0, 0, __LINE__);
	os.clockTick();	// t6 should timeout and start, then quit.
 	os.schedule();
	os.check();
	check7(0, 0, 0, 0, 0, 1, 0, __LINE__);
	check(os.timeList.next->task == &t2, fileName, __LINE__);
	check(t1.timeList.next->task == &t3, fileName, __LINE__);
	check(t2.timeList.next->task == &t5, fileName, __LINE__);
	check(t3.timeList.next->task == &t7, fileName, __LINE__);
	check(t4.timeList.next == &os.timeList, fileName, __LINE__);
	check(t5.timeList.next->task == &t1, fileName, __LINE__);
	check(t6.timeList.next->task == &t6, fileName, __LINE__);
	check(t7.timeList.next->task == &t4, fileName, __LINE__);
	os.clockTick();	// nothing should happen
 	os.schedule();
	check7(0, 0, 0, 0, 0, 1, 0, __LINE__);
	os.clockTick();	// t2 should timeout and start, then quit.
 	os.schedule();
	os.check();
	check7(0, 1, 0, 0, 0, 1, 0, __LINE__);
	check(os.timeList.next->task == &t5, fileName, __LINE__);
	check(t1.timeList.next->task == &t3, fileName, __LINE__);
	check(t2.timeList.next->task == &t2, fileName, __LINE__);
	check(t3.timeList.next->task == &t7, fileName, __LINE__);
	check(t4.timeList.next == &os.timeList, fileName, __LINE__);
	check(t5.timeList.next->task == &t1, fileName, __LINE__);
	check(t6.timeList.next->task == &t6, fileName, __LINE__);
	check(t7.timeList.next->task == &t4, fileName, __LINE__);
	os.clockTick();	// nothing should happen
 	os.schedule();
	check7(0, 1, 0, 0, 0, 1, 0, __LINE__);
	os.clockTick();	// t5 should timeout and start, then quit.
 	os.schedule();
	os.check();
	check7(0, 1, 0, 0, 1, 1, 0, __LINE__);
	check(os.timeList.next->task == &t1, fileName, __LINE__);
	check(t1.timeList.next->task == &t3, fileName, __LINE__);
	check(t2.timeList.next->task == &t2, fileName, __LINE__);
	check(t3.timeList.next->task == &t7, fileName, __LINE__);
	check(t4.timeList.next == &os.timeList, fileName, __LINE__);
	check(t5.timeList.next->task == &t5, fileName, __LINE__);
	check(t6.timeList.next->task == &t6, fileName, __LINE__);
	check(t7.timeList.next->task == &t4, fileName, __LINE__);
	os.clockTick(); os.clockTick();
 	os.schedule();
	check7(0, 1, 0, 0, 1, 1, 0, __LINE__);
	os.clockTick();	// t1 should timeout and start, then quit.
 	os.schedule();
	os.check();
	check7(1, 1, 0, 0, 1, 1, 0, __LINE__);
	check(os.timeList.next->task == &t3, fileName, __LINE__);
	check(t1.timeList.next->task == &t1, fileName, __LINE__);
	check(t2.timeList.next->task == &t2, fileName, __LINE__);
	check(t3.timeList.next->task == &t7, fileName, __LINE__);
	check(t4.timeList.next == &os.timeList, fileName, __LINE__);
	check(t5.timeList.next->task == &t5, fileName, __LINE__);
	check(t6.timeList.next->task == &t6, fileName, __LINE__);
	check(t7.timeList.next->task == &t4, fileName, __LINE__);
	os.clockTick(); os.clockTick(); os.clockTick(); os.clockTick();	
 	os.schedule();
	check7(1, 1, 0, 0, 1, 1, 0, __LINE__);
	os.clockTick();	// t3 should timeout and start, then quit.
 	os.schedule();
	os.check();
	check7(1, 1, 1, 0, 1, 1, 0, __LINE__);
	check(os.timeList.next->task == &t7, fileName, __LINE__);
	check(t1.timeList.next->task == &t1, fileName, __LINE__);
	check(t2.timeList.next->task == &t2, fileName, __LINE__);
	check(t3.timeList.next->task == &t3, fileName, __LINE__);
	check(t4.timeList.next == &os.timeList, fileName, __LINE__);
	check(t5.timeList.next->task == &t5, fileName, __LINE__);
	check(t6.timeList.next->task == &t6, fileName, __LINE__);
	check(t7.timeList.next->task == &t4, fileName, __LINE__);
	os.clockTick();	// t7 should timeout and start, then quit.
 	os.schedule();
	os.check();
	check7(1, 1, 1, 0, 1, 1, 1, __LINE__);
	check(os.timeList.next->task == &t4, fileName, __LINE__);
	check(t1.timeList.next->task == &t1, fileName, __LINE__);
	check(t2.timeList.next->task == &t2, fileName, __LINE__);
	check(t3.timeList.next->task == &t3, fileName, __LINE__);
	check(t4.timeList.next == &os.timeList, fileName, __LINE__);
	check(t5.timeList.next->task == &t5, fileName, __LINE__);
	check(t6.timeList.next->task == &t6, fileName, __LINE__);
	check(t7.timeList.next->task == &t7, fileName, __LINE__);
	os.clockTick();	// t4 should timeout and start, then quit.
 	os.schedule();
	os.check();
	check7(1, 1, 1, 1, 1, 1, 1, __LINE__);
	check(os.timeList.next == &os.timeList, fileName, __LINE__);
	check(t1.timeList.next->task == &t1, fileName, __LINE__);
	check(t2.timeList.next->task == &t2, fileName, __LINE__);
	check(t3.timeList.next->task == &t3, fileName, __LINE__);
	check(t4.timeList.next->task == &t4, fileName, __LINE__);
	check(t5.timeList.next->task == &t5, fileName, __LINE__);
	check(t6.timeList.next->task == &t6, fileName, __LINE__);
	check(t7.timeList.next->task == &t7, fileName, __LINE__);
}
