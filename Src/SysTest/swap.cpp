/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:22  $
  $Workfile:   swap.cpp  $
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
class ATask : public STask {
public:
	ATask(short priority, const char* const name):
	STask(STACK_LEN, priority, name)	{};
	~ATask() {};
	void run();
};
int count;
void ATask::run()
{
	count += 1;
}
void Test::swap()
{
	count = 0;
	/*
	 * Check that creating a stack and starting them will have the
	 * stack objects placed into the active pipe in the correct
	 * location.
	*/
	{
		os.check();
		ATask t1(1, "task 1");
		t1.start();
		check(count == 1, __FILE__, __LINE__);
		os.check();
		ATask t3(3, "task 3");
		t3.start();
		check(count == 2, __FILE__, __LINE__);
		os.check();
		ATask t2(2, "task 2");
		t2.start();
		check(count == 3, __FILE__, __LINE__);
	}
	count = 0;
	for (short i = 1; i < 500; i++)
	{
		{
			if (i % 100 == 0)
				Debug::current ->spin();
			ATask t1(1, "task 1");
			os.check();
			t1.start();
			os.check();
			check(count == i, __FILE__, __LINE__);
		}
	}
	os.check();
}
