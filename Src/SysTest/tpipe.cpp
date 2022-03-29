/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:26  $
  $Workfile:   tpipe.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <Pipe.h>
#include <test.h>
#include <debug.h>
static char* file = __FILE__;
class QTask : public STask {
	Pipe *in, *out;
public:
	QTask(short priority, const char* const name, Pipe* in, Pipe* out);
	~QTask() {};
	void run();
};
QTask::QTask(short priority, const char* const name,
		Pipe* iIn, Pipe* iOut) :
		STask(STACK_LEN, priority, name)
{
	in = iIn;
	out = iOut;
	start();
};
void QTask::run()
{
	int elem;
	for (;;)
	{
		check(in->get(&elem) == OS_DONE, file, __LINE__);
		check(out->put(elem) == OS_DONE, file, __LINE__);
	}
}
class Q1Task : public STask {
	Pipe *in;
	int* out;
public:
	Q1Task(short priority, const char* const name, Pipe* in, int* out);
	~Q1Task() {};
	void run();
};
Q1Task::Q1Task(short priority, const char* const name, Pipe* iIn, int* iOut) :
	STask(STACK_LEN, priority, name)
{
	in = iIn;
	out = iOut;
	start();
};
void Q1Task::run()
{
	int elem;
	for (;;)
	{
		check(in->get(&elem) == OS_DONE, file, __LINE__);
		*out = elem;
	}
}
void Test::pipe1()
{
	char q1[80], q2[80], q3[80], q4[80];
	os.check();
	Pipe b1(q1, elementsof(q1), OS_FIFO, "b1");
	Pipe b2(q2, elementsof(q2), OS_FIFO, "b2");
	Pipe b3(q3, elementsof(q3), OS_FIFO, "b3");
	Pipe b4(q4, elementsof(q4), OS_FIFO, "b4");
	os.check();
	register Block* bPtr = &b1;
	bPtr = (Block*) bPtr->nextBlocks->nextBlocks->nextBlocks;
	check(bPtr == &b2, file, __LINE__);
	bPtr = (Block*) bPtr->nextBlocks->nextBlocks->nextBlocks;
	check(bPtr == &b3, file, __LINE__);
	bPtr = (Block*) bPtr->nextBlocks->nextBlocks->nextBlocks;
	check(bPtr == &b4, file, __LINE__);
}
void Test::pipe2()
{
	static int priorities[] = {1,2,3,4, 4,3,2,1, 4,2,1,3, -1};
	int* priPtr = priorities;
	while (*priPtr != -1) {
		int value = 0;
		char q1[80], q2[80], q3[80], q4[80];
		Pipe b1(q1, elementsof(q1), OS_FIFO, "b1");
		Pipe b2(q2, elementsof(q2), OS_FIFO, "b2");
		Pipe b3(q3, elementsof(q3), OS_FIFO, "b3");
		Pipe b4(q4, elementsof(q4), OS_FIFO, "b4");
		QTask t1(*priPtr++, "task 1", &b1, &b2);
		QTask t2(*priPtr++, "task 2", &b2, &b3);
		QTask t3(*priPtr++, "task 3", &b3, &b4);
		Q1Task t4(*priPtr++, "task 4", &b4, &value);
		for (int i = 1; i < 1000; i++)
		{
			if (i % 100 == 0)
				Debug::current->spin();
			value = -1;
			check(b1.put(&i, sizeof(i)) == OS_DONE, file, __LINE__);
			check(value == i, file, __LINE__);
		}
	}
}
void Test::pipe3()
{
	{
		int value = 0;
		char q1[sizeof(int)], q2[sizeof(int)];
		os.check();
		Pipe b1(q1, elementsof(q1), OS_PRIORITY, "b1");
		Pipe b2(q2, elementsof(q2), OS_PRIORITY, "b2");
		os.check();
		QTask t1(1, "task 1", &b1, &b2);
		QTask t2(2, "task 2", &b1, &b2);
		QTask t3(3, "task 3", &b1, &b2);
		QTask t4(4, "task 4", &b1, &b2);
		os.check();
		check(b2.put(&value, sizeof(value)) == OS_DONE, file, __LINE__);
		check(b1.used.blockedList.next->task == &t4, file, __LINE__);
		check(b1.used.blockedList.next->next->task == &t3, file, __LINE__);
		check(b1.used.blockedList.next->next->next->task == &t2,
							file, __LINE__);
		check(b1.used.blockedList.next->next->next->next->task
					 == &t1, file, __LINE__);
		check(b1.put(&value, sizeof(value)) == OS_DONE, file, __LINE__);
		check(b1.used.blockedList.next->task == &t3, file, __LINE__);
		check(b1.used.blockedList.next->next->task == &t2, file, __LINE__);
		check(b1.used.blockedList.next->next->next->task == &t1,
							file, __LINE__);
		check(b2.free.blockedList.next->task == &t4, file, __LINE__);
		check(b1.put(&value, sizeof(value)) == OS_DONE, file, __LINE__);
		check(b1.used.blockedList.next->task == &t2, file, __LINE__);
		check(b1.used.blockedList.next->next->task == &t1, file, __LINE__);
		check(b2.free.blockedList.next->task == &t4, file, __LINE__);
		check(b2.free.blockedList.next->next->task == &t3, file, __LINE__);
		check(b1.put(&value, sizeof(value)) == OS_DONE, file, __LINE__);
		check(b1.used.blockedList.next->task == &t1, file, __LINE__);
		check(b2.free.blockedList.next->task == &t4, file, __LINE__);
		check(b2.free.blockedList.next->next->task == &t3, file, __LINE__);
		check(b2.free.blockedList.next->next->next->task == &t2,
							file, __LINE__);
		check(b1.put(&value, sizeof(value)) == OS_DONE, file, __LINE__);
		check(b2.free.blockedList.next->task == &t4, file, __LINE__);
		check(b2.free.blockedList.next->next->task == &t3, file, __LINE__);
		check(b2.free.blockedList.next->next->next->task == &t2,
							file, __LINE__);
		check(b2.free.blockedList.next->next->next->next->task
							== &t1, file, __LINE__);
	}
	static int priorities[] = {
				1,2,3,0,2,1,
				2,1,1,2,3,0,
				2,1,3,0,1,2,
				3,0,1,2,2,1,
				3,0,2,1,1,2,
				-1};
	int* priPtr = priorities;
	QTask* tasks[3];
	char q1[sizeof(int)], q2[sizeof(int)];
	while (*priPtr != -1)
	{
		Pipe b1(q1, elementsof(q1), OS_PRIORITY, "b1");
		Pipe b2(q2, elementsof(q2), OS_PRIORITY, "b2");
		int value = 0;
		QTask t1(*priPtr++, "task 1", &b1, &b2);
		tasks[*priPtr++] = &t1;
		QTask t2(*priPtr++, "task 2", &b1, &b2);
		tasks[*priPtr++] = &t2;
		QTask t3(*priPtr++, "task 3", &b1, &b2);
		tasks[*priPtr++] = &t3;
		check(b2.put(&value, sizeof(value)) == OS_DONE, file, __LINE__);
		check(b1.used.blockedList.next->task == tasks[0], file, __LINE__);
		check(b1.used.blockedList.next->next->task == tasks[1],
							file, __LINE__);
		check(b1.used.blockedList.next->next->next->task
					 == tasks[2], file, __LINE__);
	}
	{
		int value = 0;
		Pipe b1(q1, elementsof(q1), OS_PRIORITY, "b1");
		Pipe b2(q2, elementsof(q2), OS_PRIORITY, "b2");
		QTask t1(2, "task 1", &b1, &b2);
		QTask t2(4, "task 2", &b1, &b2);
		QTask t3(6, "task 3", &b1, &b2);
		check(b2.put(&value, sizeof(value)) ==OS_DONE, file, __LINE__);
		check(b1.put(&value, 1) == OS_DONE, file, __LINE__);
		QTask t4(8, "task 3", &b1, &b2);
		check(b1.put(&value,sizeof(value)-1)==OS_DONE, file, __LINE__);
		check(b1.used.blockedList.next->task == &t3, file, __LINE__);
		check(b1.used.blockedList.next->next->task == &t2,
							file, __LINE__);
		check(b1.used.blockedList.next->next->next->task
					 == &t1, file, __LINE__);
		check(b2.free.blockedList.next->task == &t4, file, __LINE__);
	}
}
void Test::pipe4()
{
	char q1[sizeof(int)], q2[sizeof(int)];
	int value;
	Pipe b2(q2, elementsof(q2), OS_PRIORITY, "b2");
	check(b2.put(&value, sizeof(value)) == OS_DONE, file, __LINE__);
	static int priorities[] = {
				2,3, 4,2, 6,1, 8,0,
				2,3, 4,2, 6,0, 5,1,
				2,2, 4,1, 6,0, 1,3,
				2,3, 4,2, 6,0, 6,1,
				2,2, 4,1, 6,0, 2,3,
				-1};
	int* priPtr = priorities;
	QTask* tasks[4];
	while (*priPtr != -1)
	{
		Pipe b1(q1, elementsof(q1), OS_PRIORITY, "b1");
		QTask t1(*priPtr++, "task 1", &b1, &b2);
		tasks[*priPtr++] = &t1;
		QTask t2(*priPtr++, "task 2", &b1, &b2);
		tasks[*priPtr++] = &t2;
		QTask t3(*priPtr++, "task 3", &b1, &b2);
		tasks[*priPtr++] = &t3;
		for (short j = 3; j > 0; j--)
			check(b1.put(&value, sizeof(value)) ==
			      OS_DONE, file, __LINE__);
		QTask t4(*priPtr++, "task 4", &b1, &b2);
		tasks[*priPtr++] = &t4;
		check(b1.put(&value,sizeof(value)) == OS_DONE, file, __LINE__);
		check(b2.free.blockedList.next->task == tasks[0], file, __LINE__);
		check(b2.free.blockedList.next->next->task == tasks[1], file, __LINE__);
		check(b2.free.blockedList.next->next->next->task == 
					tasks[2], file, __LINE__);
		check(b2.free.blockedList.next->next->next->next->task ==
							tasks[3], file, __LINE__);
	}
}
void Test::pipe()
{
	pipe1();
	pipe2();
	pipe3();
	pipe4();
}
