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
  $Workfile:   cdebug.h  $
*/

#ifndef CDEBUG_H
#define CDEBUG_H

#include <osconfig.h>
#include <osassert.h>
#include <base.h>
#include <ptrblock.h>
#include <task.h>
#include <block.h>
#include <semaphor.h>
#include <ostypes.h>
#include <debug.h>
#include <iostring.h>

/* 
CDebug
Description:
   Parent class: Debug.
   Class CDebug implements a debug class that writes output serial 
   data to the console. This can be used to print debug text 
   messages on the screen.
   Serial data is buffered until a line feed return is output,     
   or until the flush manipulator is executed.
Methods:
   CDebug::get         This is a dummy methods and does nothing.
   CDebug::doFlush     Write all buffered serial data to screen.
   CDebug::putBack     Ditto.
   CDebug::put         Output one character.
*/

class CDebug : public Debug
{
private:
	IOString str;
	char strBuf[64];
protected:
	Bool get(char*);
	Bool put(char);
	Bool doFlush();
public:
	CDebug();
	~CDebug();
	Bool putBack(char);
	virtual void spin();
};


#endif


