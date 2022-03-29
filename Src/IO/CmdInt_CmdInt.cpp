/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:36  $
  $Workfile:   cmdint.cpp  $
*/
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
#include <CmdInt.h>

/* 
CmdInt::CmdInt
Description:
   Class: CmdInt.
   CmdInt constructor.
   Initialize Command base class, and store pointers to integer 
   array, length of integer array, and bounds for each element of 
   integer array.
   Integer array is NOT initialized by CmdInt constructor to any 
   preset values.
Parameters:
   vals                This is a pointer to the external integer 
                       array that is used to store values into.
   bnds                Each element of iBounds is 2 integers, that 
                       describes the minimum and maximum values 
                       that the corresponding element of iValue 
                       can be set to.
   len                 is the number of integers in iValue.
   str                 is the Command name of this object.
   cmdHandler          is the Command.handler to link this command 
                       to.
*/

CmdInt::CmdInt(int* vals, const int* bnds, short len,
	const char* str,  CmdHandler* list) :
	Command(list, str), values(vals),
	length(len), bounds(bnds)
{
}

/* 
CmdInt::~CmdInt
Description:
   CmdInt destructor.
*/
CmdInt::~CmdInt()
{
}

