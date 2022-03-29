#include <opsys.h>
#include <memalc.h>
#include <stdlib.h>
#include <assert.h>

#define MEM_LENGTH 0x4000

MEM globalMem[MEM_LENGTH];
MemAlloc globalAlloc(globalMem, sizeof(globalMem));

void     *malloc(size_t length)
{
  void* retVal;
  OSRet err;

  err = globalAlloc.get(&retVal, (MEM) length);
  if (err != OS_DONE)
    {
      assert(0);
      retVal = 0;
    }
  return retVal;
}

void      free(void * mem)
{
  OSRet err = globalAlloc.put(mem);
  assert(err == OS_DONE);
}

