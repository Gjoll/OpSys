/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/

/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:58  $
  $Workfile:   pcclock.h  $
*/
#ifndef PCCLOCK_H
#define PCCLOCK_H

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Block.h>
#include <Semaphore.h>
#include <MemBuffer.h>
#include <OpSys.h>
#include <OsTypes.h>
#include <clock.h>

/* 
PCClock Class PCCLock
Description:
   Parent class: Clock.
   This class implements the OS clock under dos. It uses the DOS 
   interrupt 1c (hex) which is called approx. 18.2 times a second.
   Do NOT create more than one instance of any Clock class at any 
   one time!
   The file pcclkint.asm implements the actual interrupt. The CPP 
   code loads the interrupt vector in the constructor, and 
   restores the vector to its original value at exit.
Data:
   oldSeg              initial/startup segment value loaded into 
                       interrupt 0x1c at the time of construction. 
                       This is used to reload the original 
                       interrupt vector.
   oldOff              initial/startup offset value loaded into 
                       interrupt vector 0x1c.
*/

class PCClock : public Clock {
private:
	unsigned oldSeg;
	unsigned oldOff;
 	void doStart();
	void doStop();
public:
	PCClock();
	~PCClock();
};



#endif

