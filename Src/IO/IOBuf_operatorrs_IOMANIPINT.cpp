/*
{
*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:26  $
  $Workfile:   iobuf4e.cpp  $
*/
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <IoBuf.h>

IOBuf& IOBuf::operator>>(IOMANIPINT manip)
{
	return (*manip.fcn)(*this, manip.val);
};
