/*
inc,copyrite.txt}
*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:31:38  $
  $Workfile:   pipe8.cpp  $
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

OSRet Pipe::put(const int& element, OSTime timeout)
{
  return(put(&element, sizeof(element), timeout));
}

