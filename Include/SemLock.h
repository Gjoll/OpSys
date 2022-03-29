/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:24  $
  $Workfile:   Semaphore.h  $
*/
#ifndef SemLock_H
#define SemLock_H

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>

class SemLock
{
private:
protected:
  Semaphore& sem;
public:
  SemLock(Semaphore& s) : sem(s)  {sem.wait(1);};
  ~SemLock() {sem.signal(1);}
};


#endif
