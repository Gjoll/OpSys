/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/

/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:08  $
  $Workfile:   CmdSys.h  $
*/

#ifndef CMDSYS_H
#define CMDSYS_H

#include <Base.h>
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <Pipe.h>
#include <IoBuf.h>
#include <CPipe.h>
#include <CmdPipe.h>
#include <Command.h>
#include <CmdHandler.h>
#include <CmdSub.h>

/* 
CmdSystem
Description:
   Parent Class CmdSub.
   Class CmdSystem implements a Command Subsystem (CmdSub) that 
   will answer user queries as to the state of the system. The 
   output data is sent via the output CmdPipe.

   The queries answered include
   A)  Information about all tasks created in the system.
   B)  Information about all blocks created in the system. Blocks 
      include Semaphores, Pipes, and BitFlags.
   The command structure is as follows.

   (sys,[(cmd)*])      Where (cmd) can be any of the following
   (all)               Get info on all blocks and tasks.
   (blocks)            Get info on all blocks.
   (tasks)             Get info on all tasks.

   Example1.
   Get info on all tasks via "(sys,(tasks))" command.

   Task/Thread Name    is the name of the task or thread.
   Address             is the hex address of the Task/Thread 
		       object.
   Bottom              is the hex address of the bottom of the 
		       stack.
   Len                 is the length of the stack.
   Current is the current stack pointer.
   Free                is the number of bytes on the stack which 
		       have not been used. This is a 'highwater' 
		       mark and can be used to determine if the 
		       stack has overflowed.

   The following is the serial data put onto the output CmdPipe in 
   response to this command.
    Task Name        Address |-------- Stack (hex) ----------|Pri 
   State
    ---------------  -------- -Bottom- -Len -Current --Free--
   [Cmd Handler    ] 1DD001F2 1DD0022A  800 1DD008E8      53E FB 
   Active
   [OpSys::Idle    ] 1DD000C2 ******** **** ******** ******** -1 
   Active
    Thread Name       Address |-------- Stack (hex) ----------|Pri 
   State
    ---------------  -------- -Bottom- -Len -Current --Free--
   [Exit           ] 1DD01C22 1DD01B04  100 1DD01B94       90 FF 
   Blocked
   [InThread       ] 1DD01A90 1DD00A90  800 1DD01226      6F6 14 
   Blocked
   [OutThread      ] 1DD01ACA 1DD01290  800 1DD01A0C      77C 14 
   Blocked
   Example 2.
   Get info on all system blocks via the "(sys,(blocks))" command.
   Semaphores. The semaphore listing gives
   a.  the name of each semaphore,
   b.  the base address of the semaphore,
   c.  The current value of that semaphore, and
   d.  a list of any tasks that are blocked by that semaphore, and 
      how much semaphore that task is waiting for. The tasks are 
      listed in the order that they will become unblocked as the 
      semaphore is incremented.

    Semaphore Name    Address
   [comm           ] 1DD000F8    1
   [Pipe::free     ] 1DD0013C   40
   [Pipe::used     ] 1DD00158    0
   [Pipe::free     ] 1DD001A8   40
   [Pipe::used     ] 1DD001C4    0
     Task OutThread       Waiting for    1
    BitFlag Name      Address
   [Exit Flag      ] 1DD01C04  Bits    0
     ITask Exit            Waiting for Bits    1
    Pipe Name         Address
   [CommIn         ] 1DD00122 Used    0 Free    0
     Used Elements Semaphore [Pipe::used     ]  Address 1DD00158
     Free Elements Semaphore [Pipe::free     ]  Address 1DD0013C
   [CommIn         ] 1DD0018E Used    0 Free    0
     Used Elements Semaphore [Pipe::used     ]  Address 1DD001C4
     Free Elements Semaphore [Pipe::free     ]  Address 1DD001A8
    Task Name        Address |-------- Stack (hex) ----------|Pri 
   State
    ---------------  -------- -Bottom- -Len -Current --Free--
   [Cmd Handler    ] 1DD001F2 1DD0022A  800 1DD008E8      63A FB 
   Active
   [OpSys::Idle    ] 1DD000C2 ******** **** ******** ******** -1 
   Active
    Thread Name      Address |-------- Stack (hex) ----------|Pri 
   State
    ---------------  -------- -Bottom- -Len -Current --Free--
   [Exit           ] 1DD01C22 1DD01B04  100 1DD01B94       90 FF 
   Blocked
   [InThread       ] 1DD01A90 1DD00A90  800 1DD01226      6F6 14 
   Blocked
   [OutThread      ] 1DD01ACA 1DD01290  800 1DD01A0C      77C 14 
   Blocked
    Semaphore Name    Address
   [comm           ] 1DD000F8    1
   [Pipe::free     ] 1DD0013C   40
   [Pipe::used     ] 1DD00158    0
   [Pipe::free     ] 1DD001A8   40
   [Pipe::used     ] 1DD001C4    0
     Task OutThread       Waiting for    1
    BitFlag Name      Address
   [Exit Flag      ] 1DD01C04  Bits    0
     ITask Exit            Waiting for Bits    1
    Pipe Name         Address
   [CommIn         ] 1DD00122 Used    0 Free    0
     Used Elements Semaphore [Pipe::used     ]  Address 1DD00158
     Free Elements Semaphore [Pipe::free     ]  Address 1DD0013C
   [CommIn         ] 1DD0018E Used    0 Free    0
     Used Elements Semaphore [Pipe::used     ]  Address 1DD001C4
     Free Elements Semaphore [Pipe::free     ]  Address 1DD001A8
Usage:

   #include <CmdSys.h>

   extern CmdHandler main;

   CmdSystem cmdSystem(&main);
Data:
   sysInfo             This command object prints out data about 
		       all tasks and blocks.
   taskInfo            This command object print out info about 
		       all tasks.
   blockerInfo         This command object prints out info about 
		       all blockers.
*/

class SysInfo : public Command
{
 protected:
  void execute(CmdPipe* in, CmdPipe* out);
 public:
  SysInfo(CmdHandler* hlr, const char* name) :
  Command(hlr, name){};
};

class BlockerInfo : public Command
{
 protected:
  void execute(CmdPipe* in, CmdPipe* out);
 public:
  BlockerInfo(CmdHandler* hlr, const char* name) :
    Command(hlr, name) {};
};

class TaskInfo : public Command
{
 protected:
  void execute(CmdPipe* in, CmdPipe* out);
 public:
  TaskInfo(CmdHandler* hlr, const char* name) :
  Command(hlr, name) {};
};

class CmdSystem : public CmdSub
{
private:
	
	CmdHandler system;
	SysInfo sysInfo;
	TaskInfo taskInfo;
	BlockerInfo blockerInfo;
protected:
public:
	CmdSystem(CmdHandler* main);
	~CmdSystem();
};

#endif
