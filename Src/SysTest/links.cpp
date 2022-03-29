/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:30  $
  $Workfile:   links.cpp  $
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
void Test::links()
{
	os.check();
	{
		STask t1(STACK_LEN, 1, "task 1");
		os.check();
		check(testThread.taskList.last->task == &t1, __FILE__, __LINE__);
		{
			STask t3(STACK_LEN, 3, "task 3");
			os.check();
			check(testThread.taskList.last->task == &t1, __FILE__, __LINE__);
			check(t1.taskList.last->task == &t3, __FILE__, __LINE__);
			{
				STask t2(STACK_LEN, 2, "task 2");
				os.check();
				check(testThread.taskList.last->task == &t1, __FILE__, __LINE__);
				check(t1.taskList.last->task == &t2, __FILE__, __LINE__);
				check(t2.taskList.last->task == &t3, __FILE__, __LINE__);
			}
			// t2 should be deleted now ...
			os.check();
			check(testThread.taskList.last->task == &t1, __FILE__, __LINE__);
			check(t1.taskList.last->task == &t3, __FILE__, __LINE__);
		}
		// t3 should be deleted now ...
		os.check();
		check(testThread.taskList.last->task == &t1, __FILE__, __LINE__);
	}
	// t1 should be deleted now ...
	os.check();
}
