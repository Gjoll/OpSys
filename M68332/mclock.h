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
  $Workfile:   mclock.h  $
*/
#ifndef MCLOCK_H
#define MCLOCK_H

#include <osconfig.h>
#include <osassert.h>
#include <base.h>
#include <ptrblock.h>
#include <block.h>
#include <semaphor.h>
#include <membuf.h>
#include <opsys.h>
#include <ostypes.h>
#include <clock.h>
#include <int_68k.h>
/*
Mclock Class Mclock
Description:
   Parent class: Clock.
   This class implements the OS clock for a Motorola 68302.
Data:
*/
class MClock : public Clock {
private:
    VECTOR  mclockIntVec;
    short   intLevel;

	void doStart();
	void doStop();
public:
	long ticks;
	MClock( short intLevel = 3 );
	~MClock();
};

#endif

