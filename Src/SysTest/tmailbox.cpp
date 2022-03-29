/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:24  $
  $Workfile:   tmailbox.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <MailBox.h>
#include <Thread.h>
#include <test.h>
#include <debug.h>
static char* file = __FILE__;
class RTask : public STask {
	MailBox *in, *out;
public:
	RTask(short priority, const char* const name,
		MailBox* in, MailBox* out);
	~RTask() {};
	void run();
};
RTask::RTask(short priority, const char* const name,
		MailBox* iIn, MailBox* iOut) :
		STask(STACK_LEN, priority, name)
{
	in = iIn;
	out = iOut;
	start();
};
void RTask::run()
{
	long elem;
	for (;;)
	{
		check(in->get(&elem) == OS_DONE, file, __LINE__);
		check(out->put(elem) == OS_DONE, file, __LINE__);
	}
}
class R1Task : public STask {
	MailBox *in;
	long* out;
public:
	R1Task(short priority, const char* const name,
		MailBox* in, long* out);
	~R1Task() {};
	void run();
};
R1Task::R1Task(short priority, const char* const name,
		MailBox* iIn, long* iOut) :
		STask(STACK_LEN, priority, name)
{
	in = iIn;
	out = iOut;
	start();
};
void R1Task::run()
{
	long elem;
	for (;;)
	{
		check(in->get(&elem) == OS_DONE, file, __LINE__);
		*out = elem;
	}
}
void Test::mailBox1()
{
	{
		os.check();
		MailBox b1;
		MailBox b2(OS_FIFO, "b2");
		MailBox b3(OS_FIFO, "b3");
		MailBox b4(OS_FIFO, "b4");
		os.check();
		register Block* bPtr = (Block*) os.blocks.lastBlocks;
		check(bPtr == &b4, file, __LINE__);
		bPtr = (Block*) bPtr->lastBlocks;
		check(bPtr == &b3, file, __LINE__);
		bPtr = (Block*) bPtr->lastBlocks;
		check(bPtr == &b2, file, __LINE__);
		bPtr = (Block*) bPtr->lastBlocks;
		check(bPtr == &b1, file, __LINE__);
	}
	{
		os.check();
		MailBox b1(OS_FIFO, "b1");
		MailBox b2(OS_FIFO, "b2");
		MailBox b3(OS_FIFO, "b3");
		MailBox b4(OS_FIFO, "b4");
		os.check();
		long value;
		RTask t1(1, "task 1", &b1, &b2);
		RTask t2(2, "task 2", &b2, &b3);
		RTask t3(3, "task 3", &b3, &b4);
		R1Task t4(4, "task 4", &b4, &value);
		os.check();
		for (long i = 1; i < 1000; i++)
		{
			if (i % 100 == 0)
				Debug::current->spin();
			value = -1;
			check(b1.put(i) == OS_DONE, file, __LINE__);
			check(value == i, file, __LINE__);
		}
		os.check();
	}
}
void Test::mailBox2()
{
	MailBox b1(OS_PRIORITY, "b1");
	MailBox b2(OS_PRIORITY, "b2");
	static int priorities[] = {
				1,2,2,1,3,0,
				1,2,3,0,2,1,
				2,1,1,2,3,0,
				2,1,3,0,1,2,
				3,0,1,2,2,1,
				3,0,2,1,1,2,
				-1};
	int* priPtr = priorities;
	RTask* tasks[3];
	while (*priPtr != -1)
	{
		RTask t1(*priPtr++, "task 1", &b1, &b2);
		tasks[*priPtr++] = &t1;
		RTask t2(*priPtr++, "task 2", &b1, &b2);
		tasks[*priPtr++] = &t2;
		RTask t3(*priPtr++, "task 3", &b1, &b2);
		tasks[*priPtr++] = &t3;
		check(b1.blockedList.next->task == tasks[0], file, __LINE__);
		check(b1.blockedList.next->next->task == tasks[1], file, __LINE__);
		check(b1.blockedList.next->next->next->task == tasks[2],
							file, __LINE__);
		os.check();
	}
}
void Test::mailBox()
{
	{
		MailBox one(OS_FIFO, "one");
		check(one.put(1) == OS_DONE, file, __LINE__);
		check(one.put(2) == OS_MAILBOX_FULL, file, __LINE__);
	}
	mailBox1();
	mailBox2();
}
