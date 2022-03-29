/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:30  $
  $Workfile:   sleep.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <BitFlag.h>
#include <Semaphore.h>
#include <Pipe.h>
#include <OpSys.h>
#include <test.h>
static char fileName[] = __FILE__;
class SleepTask : public STask
{
private:
	short* sPtr;
	OSTime time;
	void run();
public:
	SleepTask(OSTime, short*);
	~SleepTask();
};
void SleepTask::run()
{
	sleep(time);
	*sPtr += 1;
}
SleepTask::SleepTask(OSTime iTime, short* iSPtr) :
	STask(STACK_LEN, 128)
{
	time = iTime;
	sPtr = iSPtr;
	start();
}
SleepTask::~SleepTask()
{
}
static short one;
static short two;
static short three;
static short four;
static short five;
static short six;
static short seven;
static void check7(short t1, short t2, short t3, short t4, short t5,
	short t6, short t7, short line)
{
	check(one == t1, fileName, line);
	check(two == t2, fileName, line);
	check(three == t3, fileName, line);
	check(four == t4, fileName, line);
	check(five == t5, fileName, line);
	check(six == t6, fileName, line);
	check(seven == t7, fileName, line);
}
// Clock MUST NOT be enabled for this test. If it is this
// test will fail some percentage of the time.
void Test::sleep1()
{
	one = 0;
 	os.check();
	SleepTask t1(1, &one);
 	os.check();
	check(os.timeList.next->task == &t1, fileName, __LINE__);
	check(t1.timeList.next == &os.timeList, fileName, __LINE__);
	os.swapOff();
	os.clockTick();		// task should become unblocked after
				// one clock tick
	os.check();
	os.swapOn();
	check(os.timeList.next == &os.timeList, fileName, __LINE__);
	check(t1.timeList.next->task == &t1, fileName, __LINE__);
	check(one == 0, fileName, __LINE__);	// should not have run
	os.schedule();				// cause were nonPreemptive
	check(one == 1, fileName, __LINE__);	// did task run?
}

void Test::sleep2()
{
	one = 0;
	two = 0;
	three = 0;
	four = 0;
	five = 0;
	six = 0;
	seven = 0;
 	os.check();
	SleepTask t1(10, &one);
 	os.check();
	SleepTask t2(5, &two);
 	os.check();
	SleepTask t3(15, &three);
 	os.check();
	SleepTask t4(17, &four);
 	os.check();
	SleepTask t5(7, &five);
 	os.check();
	SleepTask t6(3, &six);
	os.check();
	SleepTask t7(16, &seven);
 	os.check();
	check(os.timeList.next->task == &t6, fileName, __LINE__);
	check(t1.timeList.next->task == &t3, fileName, __LINE__);
	check(t2.timeList.next->task == &t5, fileName, __LINE__);
	check(t3.timeList.next->task == &t7, fileName, __LINE__);
	check(t4.timeList.next == &os.timeList, fileName, __LINE__);
	check(t5.timeList.next->task == &t1, fileName, __LINE__);
	check(t6.timeList.next->task == &t2, fileName, __LINE__);
	check(t7.timeList.next->task == &t4, fileName, __LINE__);
	os.clockTick(); os.clockTick();	
	os.schedule();		// Call schedule in case NO_TIMER_SWAP on
	check7(0, 0, 0, 0, 0, 0, 0, __LINE__);
	os.clockTick();	// t6 should timeout and start, then quit.
	os.schedule();		// Call schedule in case NO_TIMER_SWAP on
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
	os.schedule();		// Call schedule in case NO_TIMER_SWAP on
	check7(0, 0, 0, 0, 0, 1, 0, __LINE__);
	os.clockTick();	// t2 should timeout and start, then quit.
	os.schedule();		// Call schedule in case NO_TIMER_SWAP on
	check7(0, 1, 0, 0, 0, 1, 0, __LINE__);
	check(os.timeList.next->task == &t5, fileName, __LINE__);
	check(t1.timeList.next->task == &t3, fileName, __LINE__);
	check(t2.timeList.next->task == &t2, fileName, __LINE__);
	check(t3.timeList.next->task == &t7, fileName, __LINE__);
	check(t4.timeList.next ==  &os.timeList, fileName, __LINE__);
	check(t5.timeList.next->task == &t1, fileName, __LINE__);
	check(t6.timeList.next->task == &t6, fileName, __LINE__);
	check(t7.timeList.next->task == &t4, fileName, __LINE__);
	os.clockTick();	// nothing should happen
	os.schedule();		// Call schedule in case NO_TIMER_SWAP on
	check7(0, 1, 0, 0, 0, 1, 0, __LINE__);
	os.clockTick();	// t5 should timeout and start, then quit.
	os.schedule();		// Call schedule in case NO_TIMER_SWAP on
	check7(0, 1, 0, 0, 1, 1, 0, __LINE__);
	os.check();
	check(os.timeList.next->task == &t1, fileName, __LINE__);
	check(t1.timeList.next->task == &t3, fileName, __LINE__);
	check(t2.timeList.next->task == &t2, fileName, __LINE__);
	check(t3.timeList.next->task == &t7, fileName, __LINE__);
	check(t4.timeList.next == (TaskList*)&os.timeList, fileName, __LINE__);
	check(t5.timeList.next->task == &t5, fileName, __LINE__);
	check(t6.timeList.next->task == &t6, fileName, __LINE__);
	check(t7.timeList.next->task == &t4, fileName, __LINE__);
	os.clockTick(); os.clockTick();
	os.schedule();		// Call schedule in case NO_TIMER_SWAP on
	check7(0, 1, 0, 0, 1, 1, 0, __LINE__);
	os.clockTick();	// t1 should timeout and start, then quit.
	os.schedule();		// Call schedule in case NO_TIMER_SWAP on
	check7(1, 1, 0, 0, 1, 1, 0, __LINE__);
	os.check();
	check(os.timeList.next->task == &t3, fileName, __LINE__);
	check(t1.timeList.next->task == &t1, fileName, __LINE__);
	check(t2.timeList.next->task == &t2, fileName, __LINE__);
	check(t3.timeList.next->task == &t7, fileName, __LINE__);
	check(t4.timeList.next == (TaskList*)&os.timeList, fileName, __LINE__);
	check(t5.timeList.next->task == &t5, fileName, __LINE__);
	check(t6.timeList.next->task == &t6, fileName, __LINE__);
	check(t7.timeList.next->task == &t4, fileName, __LINE__);
	os.clockTick(); os.clockTick(); os.clockTick(); os.clockTick();
	os.schedule();		// Call schedule in case NO_TIMER_SWAP on
	check7(1, 1, 0, 0, 1, 1, 0, __LINE__);
	os.clockTick();	// t3 should timeout and start, then quit.
	os.schedule();		// Call schedule in case NO_TIMER_SWAP on
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
	os.schedule();		// Call schedule in case NO_TIMER_SWAP on
	check7(1, 1, 1, 0, 1, 1, 1, __LINE__);
	os.check();
	check(os.timeList.next->task == &t4, fileName, __LINE__);
	check(t1.timeList.next->task == &t1, fileName, __LINE__);
	check(t2.timeList.next->task == &t2, fileName, __LINE__);
	check(t3.timeList.next->task == &t3, fileName, __LINE__);
	check(t4.timeList.next == &os.timeList, fileName, __LINE__);
	check(t5.timeList.next->task == &t5, fileName, __LINE__);
	check(t6.timeList.next->task == &t6, fileName, __LINE__);
	check(t7.timeList.next->task == &t7, fileName, __LINE__);
	os.clockTick();	// t4 should timeout and start, then quit.
	os.schedule();		// Call schedule in case NO_TIMER_SWAP on
	check7(1, 1, 1, 1, 1, 1, 1, __LINE__);
	os.check();
	check(os.timeList.next == &os.timeList, fileName, __LINE__);
	check(t1.timeList.next->task == &t1, fileName, __LINE__);
	check(t2.timeList.next->task == &t2, fileName, __LINE__);
	check(t3.timeList.next->task == &t3, fileName, __LINE__);
	check(t4.timeList.next->task == &t4, fileName, __LINE__);
	check(t5.timeList.next->task == &t5, fileName, __LINE__);
	check(t6.timeList.next->task == &t6, fileName, __LINE__);
	check(t7.timeList.next->task == &t7, fileName, __LINE__);
}


void Test::sleep4()
{
	one = 0;
	os.check();
	SleepTask t1(10, &one);
	t1.stop();
	os.check();
}
