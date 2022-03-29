/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/

/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:56  $
  $Workfile:   rtclock.h  $
*/

#ifndef RTCLOCK_H
#define RTCLOCK_H

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
RTClock Class RTClock
Description:
   Parent class: Clock.
   This class implements the OS clock under dos. It uses the DOS 
   interrupt 70 (hex) which is called 1024 times a second.
   The file rtClkFun.asm implements the actual interrupt. The CPP 
   code loads the interrupt vector in the constructor, and 
   restores the vector to its original value at exit.

   RTClock will save the current interrupt 0x70 vector, PIC 
   settings for the real time clock, and the current settings of 
   the real time clock setup registers at construction, and reset 
   them at destruction.
Bugs:

   **** Please Read ****

   Using RTClock will cause your time of day clock to get 
   confused. This will show itself on boot, when the BIOS will 
   require you to reset the setup parameters, and will clear the 
   time and date. The other setup parameters appear to be ok. Use 
   at your own risk.
Data:
   oldSeg              initial/boot interrupt vector 0x70 segment 
                       value
   oldOff              initial/boot interrupt vector 0x70 offset 
                       value.
   statusA             initial real time clock statusA register 
                       value.
   statusB             initial real time clock statusA register 
                       value.
   pic1                initial PIC 1 setting for real time clock 
                       interrupt.
   pic2                initial PIC 2 setting for real time clock 
                       interrupt.
   clocks              Number of real tie clocks created.
Methods:
   RTClock             Constructor.
   ~RTClock            Destructor.
   RTClock::doStart    Start real time clock.
   RTClock::doStop     Stop real time clock.
   RTClock::write      Private. Write to real time clock.
   RTClock::read       private. Read from real time clock.
*/

enum RTFreq {
	TICKS_32768=0x1,		// 32768 ticks/sec.
	TICKS_16384=0x2,		// 16384 ticks/sec.
	TICKS_8192=0x3,			// 8192 ticks/sec.
	TICKS_4096=0x4,			// 4096 ticks/sec.
	TICKS_2048=0x5,			// 2048 ticks/sec.
	TICKS_1024=0x6,			// 1024 ticks/sec.
	TICKS_512=0x7,			// 512 ticks/sec.
	TICKS_256=0x8,			// 256 ticks/sec.
	TICKS_128=0x9,			// 128 ticks/sec.
	TICKS_64=0xA,			// 64 ticks/sec.
	TICKS_32=0xb,			// 32 ticks/sec.
	TICKS_16=0xc,			// 16 ticks/sec.
	TICKS_8=0xd,			// 8 ticks/sec.
	TICKS_4=0xe,			// 4 ticks/sec.
	TICKS_2=0xf,			// 2 ticks/sec.
};

class RTClock : public Clock {
private:
	unsigned oldSeg;
	unsigned oldOff;
	unsigned char statusA;
	unsigned char statusB;
	unsigned char pic1;
	unsigned char pic2;
	void write(short address, unsigned char value);
	int read(short address);
	void doStart();
	void doStop();
public:
	RTClock(RTFreq);
	~RTClock();
};



#endif

