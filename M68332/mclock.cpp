/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.
*/

/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:33:54  $
  $Workfile:   MClock.cpp  $
*/

#include <osconfig.h>
#include <assert.h>
#include <base.h>
#include <ptrblock.h>
#include <block.h>
#include <semaphor.h>
#include <membuf.h>
#include <opsys.h>
#include <ostypes.h>
#include <clock.h>
#include <MClock.h>

extern MClock clock;
extern "C" void interrupt MClockInt();
void interrupt MClockInt()
{
    clock.ticks++;
	os.clockTick();
}

/*
MClock::MClock
Description:
   Class: MClock.
   MClock constructor. Link interrupt routine MClkInt to the 68332
   periodic timer, and start clock interrupts.
   Parent class Clock() is called with True specifying that the
   operating system routine OpSys::clockTick() called by MClkInt
   can perform a task switch. Any tasks that become unblocked
   because of OpSys::clockTick() will be swapped to immediately.
*/

// MCR     equ     $FFFA00+MOD_MAP_OFFSET
// PICR    equ     MCR+$22
// PITR    equ     MCR+$24


/*
   MClock::MClock()
   Constructor. Install interrupt vector, and start clock
   running.
*/
MClock::MClock( short IntLevel ) : Clock(OSFalse, 100l),
        intLevel( IntLevel )
{
  ticks = 0;
//    install MClockInt at next available vector entry..
  mclockIntVec = interrupt_68k.setHandler( MClockInt );
// start the clock
  start();
}


/*
MClock::~MClock
Description:
   Class: MClock.
   MClock destructor.
*/

MClock::~MClock()
{
	stop();
}

/*
MClock::doStart
Description:
   Class: MClock.
   Start the clock interrupt.
*/

void MClock::doStart()
{
    *((short*) (0xfffa24)) = (short) 0x0052;   // set PITR register for 10 mSec
    *((short*) (0xFFFA22)) = (short) (mclockIntVec | (intLevel << 8));
}



/*
MClock::doStop
Description:
   Class: MClock.
   Stop clock interrupts.
*/

void MClock::doStop()
{
  asm("   move.w #0,$FFFA22"); //stop periodic interrupts.
}


