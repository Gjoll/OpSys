/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:04  $
  $Workfile:   CmdInt.h  $
*/
#ifndef CMDINT_H
#define CMDINT_H
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
#include <CmdHdr.h>
#include <Command.h>
#include <CmdHandler.h>
/* 
CmdInt
Description:
   Parent Class: Command$.
   CmdInt is a class of command processor objects that set and 
   return integer values of an integer array via a CmdPipe.
   To set this object, (Command Name,Value1) should be placed into 
   the CmdPipe stream that the CmdHandler this task is linked to 
   reads. Command Name is the ASCII name of this command, Value is 
   a comma separated  list of integer values. There should be 
   exactly as many values as there are elements in *values, and 
   each setting must be with in the values established by the 
   bounds array. When setting the value of a CmdInt object, the 
   following will always be returned.
   (Command Name,Status)
   Where status is one of the following strings (case is exactly 
   as shown).
   ok  Operation was successfull.
   badCount        ncorrect number of values was sent. There must 
   be exactly as many values sent as there are values in the 
   CmdInt object.
   outOfBounds One or more of the values passed were too large or 
   too small.
   To read the current value, (Command) should be sent, and 
   (Command,value1,value2,..valuex) will be returned.
   More than one integer value can be associated with this object, 
   that is the Class defines an array of integers. The class also 
   defines individual minimum and maximum values for each value of 
   the class. The class will return an error if the user attempts 
   to set any of the values to an out of bounds value, and not set 
   the values.

    ------------      (parse)       --------------
   | CmdHandler |  <-------------  | Command Task |
    ------------                    --------------
	  |
	-----------
       | Command 1 |
	-----------
	  |
	-----------
       | Command 2 |
	-----------
	  |
	-----------
       | Command 3 |
	-----------
Usage:

   #include <CmdInt.h>
   #define VALUES_SIZE ???

   extern CmdHandler cmdHandler;
   extern int values[VALUES_SIZE];
   extern int bounds[VALUES_SIZE * 2];

   CmdInt cmdInt(values, bounds, "CmdInt-Name", &cmdHandler);

   Examples:
   Assume Name is the ascii name for this CmdInt object, there are 
		       3 elements and the bounds array specifies 
		       that each element of the array must be in 
		       the range 1..3.
   #                   Command         Response
   1                   (Name,1)        (Name,badCount)
   2                   (Name,1,2,4)        (Name,outOfBounds)
   3                   (Name,3,2,1)        (Name,3,2,1)
   4                   (Name)          (Name,3,2,1)

   1 The command specified too few parameters. This CmdInt is an 
		       array of 3 elements, only one value was 
		       set. This caused the badCount message to be 
		       returned.

   2 The command tried to set the third element of CmdInt to a 
		       value that was too large. The bounds array 
		       passed to CmdInt specified that each 
		       element was to be in the range 1..3. This 
		       caused the outOfBounds message to be 
		       returned.

   3. This command was correct. The CmdInt was set to 3,2,1. The 
		       current setting is returned.

   4. This command was correct. Since nothing was set, the current 
		       values of the CmdInt were returned.
Data:
   values              is a pointer to the user supplied array to 
		       store the new values into.
   length              is the number of elements (integers) in the 
		       array *values.
   bounds              is an optional array that contains 2 
		       elements for each element of values. Each 
		       of these 2 elements are the min and max 
		       value for the corresponding element of 
		       values. An error will be returned if the 
		       user attempts to set element of values out 
		       of bounds.
Methods:
   CmdInt::CmdInt      Constructor.
   CmdInt::~CmdInt     Destructor.
   CmdInt::execute     is called when the Command.handler that 
		       this object is linked to finds a command 
		       that matches the name of this CmdInt 
		       object.
*/

#define MAX_CMD_INTS 10

class CmdInt : public Command
{
 private:
 protected:
  int* values;
  int length;
  const int* bounds;
  void execute(CmdPipe* in, CmdPipe* out);
 public:
  CmdInt(int* values, const int* bounds, short, const char*,
	 CmdHandler*);
  ~CmdInt();
};

#endif
