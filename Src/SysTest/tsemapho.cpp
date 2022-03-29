/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:28  $
  $Workfile:   tsemapho.cpp  $
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
class JTask : public STask {
	Semaphore *wait, *signal;
	int* counter;
	int count;
public:
	JTask(short priority, const char* const name,
		Semaphore* wait, Semaphore* signal, int* counter,
		int count = 1);
	~JTask() {};
	void run();
};
static char* file = __FILE__;
JTask::JTask(short priority, const char* const name,
	Semaphore* iWait, Semaphore* iSignal, int* iCounter, int iCount) :
	STask(STACK_LEN, priority, name)
{
	count = iCount;
	wait = iWait;
	counter = iCounter;
	signal = iSignal;
	start();
};
void JTask::run()
{
	for (;;)
	{
		check(wait->wait(count) == OS_DONE, file, __LINE__);
		*counter += 1;
		check(signal->signal() == OS_DONE, file, __LINE__);
	}
}
void Test::semaphore1()
{
	int counter[3];
	counter[0] = counter[1] = counter[2] = 0;
	static int vals1[] = {1,1,1};
	static int vals2[] = {26,26,26};
	Semaphore b1(0, OS_FIFO, "b1");
	Semaphore b2(0, OS_FIFO, "b2");
	Semaphore b3(0, OS_FIFO, "b3");
	Semaphore b4(0, OS_FIFO, "b4");
	os.check();
	check(b1.wait(1) == OS_BLOCKERR, file, __LINE__);
	check(os.blocks.lastBlocks == &b4, file, __LINE__);
	check(b4.lastBlocks == &b3, file, __LINE__);
	check(b3.lastBlocks == &b2, file, __LINE__);
	check(b2.lastBlocks == &b1, file, __LINE__);
	JTask t1(1, "task 1", &b1, &b2, counter);
	JTask t2(2, "task 2", &b2, &b3, counter+1);
	JTask t3(3, "task 3", &b3, &b4, counter+2);
	os.check();
	check(b1.blockedList.next->task == &t1, file, __LINE__);
	check(b2.blockedList.next->task == &t2, file, __LINE__);
	check(b3.blockedList.next->task == &t3, file, __LINE__);
	check(b1.signal(1) == OS_DONE, file, __LINE__);
	os.check();
	check(b1.value() == 0, file, __LINE__);
	check(b2.value() == 0, file, __LINE__);
	check(b3.value() == 0, file, __LINE__);
	check(b4.value() == 1, file, __LINE__);
	check(counter, vals1, elementsof(vals1), file, __LINE__);
	check(b1.signal(25) == OS_DONE, file, __LINE__);
	os.check();
	check(b1.value() == 0, file, __LINE__);
	check(b2.value() == 0, file, __LINE__);
	check(b3.value() == 0, file, __LINE__);
	check(b4.value() == 26, file, __LINE__);
	check(counter, vals2, elementsof(vals2), file, __LINE__);
	for (short i = 27; i < 10000; i++)
	{
		if (i % 250 == 0)
			Debug::current->spin();
		check(b1.signal(1) == OS_DONE, file, __LINE__);
		check(b1.value() == 0, file, __LINE__);
		check(b2.value() == 0, file, __LINE__);
		check(b3.value() == 0, file, __LINE__);
		check(b4.value() == i, file, __LINE__);
		check(counter[0] == i, file, __LINE__);
		check(counter[1] == i, file, __LINE__);
		check(counter[2] == i, file, __LINE__);
	}
	os.check();
}
void Test::semaphore2()
{
	static int vals1[] = {0,0,0};
	static int vals2[] = {0,0,1};
	static int vals3[] = {0,1,2};
	static int vals4[] = {1,2,3};
	static int vals5[] = {0,1};
	static int vals6[] = {1,2};
	static int vals7[] = {0,2};
	static int vals8[] = {0,4};
	static int vals9[] = {0,5};
	static int vals10[] = {1,6};
	static int vals11[] = {2,7};
	static int vals12[] = {2,8};
	static int vals13[] = {3,10};
	int counter[3];
	counter[0] = 0;
	counter[1] = 0;
	counter[2] = 0;
	Semaphore b1(0, OS_PRIORITY, "b1");
	Semaphore b2(0, OS_PRIORITY, "b2");
	Semaphore b3(0, OS_PRIORITY, "b3");
	Semaphore b4(0, OS_PRIORITY, "b4");
	static int priorities[] = {
				1,2,2,1,3,0,
				1,2,3,0,2,1,
				2,1,1,2,3,0,
				2,1,3,0,1,2,
				3,0,1,2,2,1,
				3,0,2,1,1,2,
				-1};
	int* priPtr = priorities;
	JTask* tasks[3];
	while (*priPtr != -1)
	{
		// Make sure that tasks are put onto blocked list in order of
		// task priority.
		JTask t1(*priPtr++, "t1", &b1, &b2, counter);
		tasks[*priPtr++] = &t1;
		JTask t2(*priPtr++, "t2", &b1, &b2, counter+2);
		tasks[*priPtr++] = &t2;
		JTask t3(*priPtr++, "t3", &b1, &b2, counter+1);
		tasks[*priPtr++] = &t3;
		check(b1.blockedList.next->task == tasks[0], file, __LINE__);
		check(b1.blockedList.next->next->task == tasks[1], file, __LINE__);
		check(b1.blockedList.next->next->next->task == tasks[2],
			file, __LINE__);
		os.check();
	}
	{
		// Make sure that tasks are put onto blocked list in order of
		// task priority.
		JTask t1(1, "t1", &b1, &b2, counter);
		JTask t2(2, "t2", &b1, &b2, counter+1);
		JTask t3(3, "t3", &b1, &b2, counter+2);
		check(b1.blockedList.next->task == &t3, file, __LINE__);
		check(b1.blockedList.next->next->task == &t2, file, __LINE__);
		check(b1.blockedList.next->next->next->task == &t1,
			file, __LINE__);
                check(counter, vals1, elementsof(vals1), file, __LINE__);
		// signal once. Tasks should still be in same order.
		b1.signal(1);
		check(b1.blockedList.next->task == &t3, file, __LINE__);
		check(b1.blockedList.next->next->task == &t2, file, __LINE__);
		check(b1.blockedList.next->next->next->task == &t1,
			file, __LINE__);
		check(counter, vals2, elementsof(vals2), file, __LINE__);
		os.check();
		// signal twice. Tasks should still be in same order.
		b1.signal(2);
		check(b1.blockedList.next->task == &t3, file, __LINE__);
		check(b1.blockedList.next->next->task == &t2, file, __LINE__);
		check(b1.blockedList.next->next->next->task == &t1,
			file, __LINE__);
		check(counter, vals3, elementsof(vals3), file, __LINE__);
		os.check();
		// signal thrice. Tasks should still be in same order.
		b1.signal(3);
		check(b1.blockedList.next->task == &t3, file, __LINE__);
		check(b1.blockedList.next->next->task == &t2, file, __LINE__);
		check(b1.blockedList.next->next->next->task == &t1,
			file, __LINE__);
		check(counter, vals4, elementsof(vals4), file, __LINE__);
		os.check();
		// signal 4x. Tasks should still be in same order.
		b1.signal(4);
		check(b1.blockedList.next->task == &t3, file, __LINE__);
		check(b1.blockedList.next->next->task == &t2, file, __LINE__);
		check(b1.blockedList.next->next->next->task == &t1,
			file, __LINE__);
		check(counter[2] == 5, file, __LINE__);
		check(counter[1] == 3, file, __LINE__);
		check(counter[0] == 2, file, __LINE__);
		os.check();
	}
	{
		counter[0] = 0;
		counter[1] = 0;
		counter[2] = 0;
		// Make sure that tasks are put onto blocked list in order of
		// task priority.
		JTask t1(1,"t1",&b1,&b2,counter,4);
		b1.signal(1);
		JTask t2(2,"t2",&b1,&b2,counter+1,1);
		check(counter, vals5, elementsof(vals5), file, __LINE__);
		b1.signal(5);
		check(counter, vals6, elementsof(vals6), file, __LINE__);
	}
	{
		counter[0] = 0;
		counter[1] = 0;
		counter[2] = 0;
		// Make sure that tasks are put onto blocked list in order of
		// task priority.
		JTask t1(1,"t1",&b1,&b2,counter,4);
		JTask t2(2,"t2",&b1,&b2,counter+1,2);
		b1.signal(4);
		check(counter, vals7, elementsof(vals7), file, __LINE__);
		b1.signal(5);
		check(counter, vals8, elementsof(vals8), file, __LINE__);
		b1.signal(1);
		check(counter, vals9, elementsof(vals9), file, __LINE__);
		b1.signal(6);
		check(counter, vals10, elementsof(vals10), file, __LINE__);
		b1.signal(7);
		check(counter, vals11, elementsof(vals11), file, __LINE__);
		b1.signal(1);
		check(counter, vals12, elementsof(vals12), file, __LINE__);
		b1.signal(8);
		check(counter, vals13, elementsof(vals13), file, __LINE__);
	}
}
