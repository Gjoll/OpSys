/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:26  $
  $Workfile:   tmem.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <MemBuffer.h>
#include <Pipe.h>
#include <Thread.h>
#include <test.h>
#include <debug.h>

int counter = 0;
static char* fileName = __FILE__;

void tMem1(Thread*, void* vMem)
{
	char* ptr;
	OSRet retVal;
	MemBuffer* mem = (MemBuffer*) vMem;
	for (;;) {
		retVal = mem->get((void**) &ptr, 1);
		check((retVal == OS_DONE), fileName, __LINE__);
		counter += 1;
	}
}

struct PCBuf {
	Pipe* pipe;
	MemBuffer* mem;
} ;

static void producer(Thread*, void* data)
{
	int* ptr;
	OSRet retVal;
	PCBuf* sPtr = (PCBuf*) data;
	short counter = 0;
	for (counter = 0; counter < 10000; counter++) {
		retVal = sPtr->mem->get((void**) &ptr, sizeof(*ptr));
		check((retVal == OS_DONE), fileName, __LINE__);
		*ptr = counter;
		retVal = sPtr->pipe->put(&ptr, sizeof(ptr));
		check((retVal == OS_DONE), fileName, __LINE__);
		if (counter % 500 == 0)
			Debug::current->spin();
	}
}

static void consumer(Thread*, void* data)
{
	int* ptr;
	OSRet retVal;
	PCBuf* sPtr = (PCBuf*) data;
	short counter = 0;
	for (;;) {
		retVal = sPtr->pipe->get((void*) &ptr, sizeof(ptr));
		check((retVal == OS_DONE), fileName, __LINE__);
		check(*ptr == counter, fileName, __LINE__);
		sPtr->mem->put((void*) ptr);
		check((retVal == OS_DONE), fileName, __LINE__);
		counter += 1;
	}
}

void Test::tMemBuffer()
{
	{
		MEM buffer[MEMBUFSIZE(5, 1)];
		MemBuffer mem(buffer, sizeof(buffer), 1, OS_FIFO);
		counter = 0;
		check(mem.value() == 5, fileName, __LINE__);
		check(buffer[0] == 1, fileName, __LINE__);
		check(buffer[1] == 2, fileName, __LINE__);
		check(buffer[2] == 3, fileName, __LINE__);
		check(buffer[3] == 4, fileName, __LINE__);
		check(buffer[4] == (unsigned int) -1, fileName, __LINE__);
		Thread test1(tMem1, (void*) &mem,
			STACK_LEN, MAX_PRIORITY, "TMem1");
		check(counter == 5, fileName, __LINE__);
	}
	{
		MEM buffer[MEMBUFSIZE(1, sizeof(MEM)+1)];
		MemBuffer mem(buffer,sizeof(buffer), sizeof(MEM)+1, OS_FIFO);
		counter = 0;
		check(mem.value() == 1, fileName, __LINE__);
		check(buffer[0] == (unsigned int) -1, fileName, __LINE__);
		Thread test1(tMem1, (void*) &mem,
			STACK_LEN, MAX_PRIORITY, "TMem1");
		check(counter == 1, fileName, __LINE__);
	}
	{
		MEM buffer[MEMBUFSIZE(10, 4 * sizeof(MEM)+1)];
		MemBuffer mem(buffer,sizeof(buffer), 4*sizeof(MEM)+1, OS_FIFO);
		counter = 0;
		check(mem.value() == 10, fileName, __LINE__);
		check(mem.size == 5, fileName, __LINE__);
		check(mem.length == 10, fileName, __LINE__);
		check(buffer[0] == 5, fileName, __LINE__);
		check(buffer[5] == 10, fileName, __LINE__);
		check(buffer[10] == 15, fileName, __LINE__);
		check(buffer[15] == 20, fileName, __LINE__);
		check(buffer[20] == 25, fileName, __LINE__);
		check(buffer[25] == 30, fileName, __LINE__);
		check(buffer[30] == 35, fileName, __LINE__);
		check(buffer[35] == 40, fileName, __LINE__);
		check(buffer[40] == 45, fileName, __LINE__);
		check(buffer[45] == (unsigned int) -1, fileName, __LINE__);
		Thread test1(tMem1, (void*) &mem,
			STACK_LEN, MAX_PRIORITY, "TMem1");
		check(counter == 10, fileName, __LINE__);
	}
	{
		MEM buffer[MEMBUFSIZE(4, sizeof(MEM))];
		MemBuffer mem(buffer,sizeof(buffer), sizeof(MEM), OS_FIFO);
		char pipeBuf[20];
		Pipe pipe(pipeBuf, sizeof(pipeBuf), OS_FIFO, "PD Pipe");
		PCBuf pcBuf;
		pcBuf.pipe= &pipe;
		pcBuf.mem = &mem;
		counter = 0;
		Thread test1(consumer, (void*) &pcBuf,
			STACK_LEN, MAX_PRIORITY - 1, "consumer");
		Thread test2(producer, (void*) &pcBuf,
			2 * STACK_LEN, MAX_PRIORITY, "producer");
		check(mem.value() == 4, fileName, __LINE__);
	}
}
