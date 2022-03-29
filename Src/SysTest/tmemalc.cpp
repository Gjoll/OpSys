/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:26  $
  $Workfile:   tmemalc.cpp  $
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
#include <MemAlloc.h>

static char* fileName = __FILE__;
#define SIZE(i) (HDR_LENGTH + i)

void Test::tMemAlloc()
{
  {
    MEM buffer[10 * HDR_LENGTH];
    MemAlloc m(buffer, sizeof(buffer));
    void* memory;
    void* memory1;

    check(m.get(&memory, (8*HDR_LENGTH)*sizeof(MEM))== OS_DONE,
	  fileName, __LINE__);
    check(memory == (void*) &buffer[2 * HDR_LENGTH], fileName,
	  __LINE__);
    check(m.get(&memory1, 1) == OS_NO_ROOM, fileName,
	  __LINE__);
    check(m.put(memory)== OS_DONE, fileName, __LINE__);
    check(m.get(&memory, 8 * HDR_LENGTH) == OS_DONE, fileName,
	  __LINE__);
    check(memory == (void*) &buffer[2 * HDR_LENGTH], fileName,
	  __LINE__);
  }

  {
    MEM buffer[HDR_LENGTH + (HDR_LENGTH + 5) * 5];
    MemAlloc m(buffer, sizeof(buffer));
    void* mem[5];
    void* memory1;
    short add = 2 * HDR_LENGTH;
    short i;

    for (i = 0; i < 5; i++)
      {
	check(m.get(&mem[i], i * sizeof(MEM))== OS_DONE, fileName,
	      __LINE__);
	check(mem[i] == (void*) &buffer[add],
	fileName, __LINE__);
	add += SIZE(i);
      }
    check(m.put(mem[4])== OS_DONE, fileName, __LINE__);
    add -= SIZE(4);
    short size = SIZE(4) - HDR_LENGTH;

    for (i = 3; i >= 0; i--)
      {
	check(m.put(mem[i])== OS_DONE, fileName, __LINE__);
	size += SIZE(i);
	add -= SIZE(i);
	check(m.get(&memory1, size * sizeof(MEM))== OS_DONE,
	      fileName, __LINE__);
	check(memory1 == (void*) &buffer[add],
	      fileName, __LINE__);
	check(m.put(memory1)== OS_DONE, fileName, __LINE__);
      }
  }

  {
    MEM buffer[HDR_LENGTH + (HDR_LENGTH + 5) * 5];
    MemAlloc m(buffer, sizeof(buffer));
    short add = 2 * HDR_LENGTH;
    void* mem[5];
    void* memory1;
    short i;

    for (i = 0; i < 5; i++)
      {
	check(m.get(&mem[i], i * sizeof(MEM))== OS_DONE, fileName,
	      __LINE__);
	check(mem[i] == (void*) &buffer[add],
	fileName, __LINE__);
	add += SIZE(i);
      }
    check(m.put(mem[0])== OS_DONE, fileName, __LINE__);
    add -= SIZE(0);
    short size = SIZE(0) - HDR_LENGTH;

    for (i = 1; i < 5; i++)
      {
	check(m.put(mem[i])== OS_DONE, fileName, __LINE__);
	size += SIZE(i);
	check(m.get(&memory1, size * sizeof(MEM))== OS_DONE,
	      fileName, __LINE__);
	check(memory1 == (void*) &buffer[2*HDR_LENGTH],
	      fileName, __LINE__);
	check(m.put(memory1)== OS_DONE, fileName, __LINE__);
      }
  }

  {
    MEM buffer[HDR_LENGTH + (HDR_LENGTH + 5) * 5];
    MemAlloc m(buffer, sizeof(buffer));
    short add = 2 * HDR_LENGTH;
    void* mem[5];
    void* memory1;

    for (short i = 0; i < 5; i++)
      {
	check(m.get(&mem[i], i * sizeof(MEM))== OS_DONE, fileName,
	      __LINE__);
	check(mem[i] == (void*) &buffer[add],
	fileName, __LINE__);
	add += SIZE(i);
      }
    check(m.put(mem[0])== OS_DONE, fileName, __LINE__);
    check(m.put(mem[2])== OS_DONE, fileName, __LINE__);
    check(m.put(mem[1])== OS_DONE, fileName, __LINE__);
    check(m.get(&memory1, 2*HDR_LENGTH+3*sizeof(MEM))== OS_DONE,
	  fileName, __LINE__);
    check(memory1 == (void*) &buffer[2*HDR_LENGTH],
	  fileName, __LINE__);
    check(m.put(memory1)== OS_DONE, fileName, __LINE__);
  }
}
