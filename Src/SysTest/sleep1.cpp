/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:30  $
  $Workfile:   sleep1.cpp  $
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
#include <BitFlag.h>
#include <Thread.h>
#include <test.h>
#include <debug.h>
class BitTimeout : public STask
{
private:
	VOLATILE short* sPtr;
	OSTime time;
	void run();
	BitFlag flag;
public:
	BitTimeout(OSTime, VOLATILE short*);
};
void BitTimeout::run()
{
	if (flag.wait(0xff, OS_ALL, time) != OS_TIMEOUT)
   {
		(*Debug::current) << "Test Failed file. OS_TIMEOUT not returned "
      			<< __FILE__ << " line " << __LINE__ << endl;
   	os.exit(1);
	}
	*sPtr += 1;
}
BitTimeout::BitTimeout(OSTime iTime, VOLATILE short* iSPtr) :
	STask(STACK_LEN, 128), flag("BitFlag 1")
{
	time = iTime;
	sPtr = iSPtr;
	start();
}
class SemTimeout : public STask
{
private:
	VOLATILE short* sPtr;
	OSTime time;
	void run();
	Semaphore flag;
public:
	SemTimeout(OSTime, VOLATILE short*);
};
void SemTimeout::run()
{
	if (flag.wait(1, time) != OS_TIMEOUT)
   {
		(*Debug::current) << "Test Failed file. OS_TIMEOUT not returned "
      			<< __FILE__ << " line " << __LINE__ << endl;
   	os.exit(1);
	}
	*sPtr += 1;
}
SemTimeout::SemTimeout(OSTime iTime, VOLATILE short* iSPtr) :
	STask(STACK_LEN, 128), flag(0, OS_FIFO, "Semaphore 1")
{
	time = iTime;
	sPtr = iSPtr;
	start();
}
class Pipe1Timeout : public STask
{
private:
	VOLATILE short* sPtr;
	OSTime time;
	void run();
	Pipe pipe;
	char pipeBuf[10];
public:
	Pipe1Timeout(OSTime, VOLATILE short*);
};
void Pipe1Timeout::run()
{
	char c;
	pipe.get(&c, 1, time);
	*sPtr += 1;
}
Pipe1Timeout::Pipe1Timeout(OSTime iTime,VOLATILE short* iSPtr):
	STask(STACK_LEN, 128),
	pipe(pipeBuf, sizeof(pipeBuf), OS_FIFO, "Pipe")
{
	time = iTime;
	sPtr = iSPtr;
	start();
}
class Pipe2Timeout : public STask
{
private:
	VOLATILE short* sPtr;
	OSTime time;
	void run();
	Pipe pipe;
	char pipeBuf[10];
public:
	Pipe2Timeout(OSTime, VOLATILE short*);
};
void Pipe2Timeout::run()
{
	for (short i = 0; i < sizeof(pipeBuf); i++)
		pipe.put('a', time);
	*sPtr += 1;
}
Pipe2Timeout::Pipe2Timeout(OSTime iTime, VOLATILE short* iSPtr) :
	STask(STACK_LEN, 128),
	pipe(pipeBuf, sizeof(pipeBuf), OS_FIFO, "Pipe")
{
	time = iTime;
	sPtr = iSPtr;
	start();
}
void checkTime(OSTime early, OSTime late, short length, int line)
{
	OSTime theTime = os.now();
	OSTime first = os.elapsedTime(early, theTime);
	OSTime second = os.elapsedTime(late, theTime);
	if ((first < length) || (second > length + 1)) {
		disInts();
		(*Debug::current) << "Test Failed file " << __FILE__ << " line " <<
			line << endl;
		(*Debug::current) << "Elapsed time was " << first << ".." << second <<
		" should have been " << length << endl;
	}
}
void Test::sleep3()
{
	VOLATILE short one = 0;
	VOLATILE short two = 0;
	VOLATILE short three = 0;
	VOLATILE short four = 0;
	OSTime time1a, time1b;
	OSTime time2a, time2b;
	OSTime time3a, time3b;
	time1a = os.now();
	BitTimeout bitTO(10, &one);
	time1b = os.now();
	time2a = os.now();
	SemTimeout semTO(20, &two);
	time2b = os.now();
	time3a = os.now();
	Pipe1Timeout p1TO(50, &three);
	Pipe2Timeout p2TO(50, &four);
	time3b = os.now();
	while (one == 0)
		os.schedule();
	checkTime(time1a, time1b, 10, __LINE__);
	(*Debug::current).spin();
	while (two == 0)
		os.schedule();
	checkTime(time2a, time2b, 20, __LINE__);
	(*Debug::current).spin();
	while (three == 0)
		os.schedule();
	while (four == 0)
		os.schedule();
	checkTime(time3a, time3b, 50, __LINE__);
	(*Debug::current).spin();
}
