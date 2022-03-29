/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision:   2.1  $
  $Modtime:   01 May 1993 09:34:28  $
  $Workfile:   cdebug.h  $
*/
#ifndef CDEBUG_H
#define CDEBUG_H
#include <debug.h>
/* 
CDebug
Description:
   Class CDebug implements a debug output pipe that writes the 
   output directly to the console. This can be used to print debug 
   text messages on the screen.
Methods:
   get                 This is a dummy methods and does nothing.
   doFlush             Ditto.
   put                 Output one character.
   See Also: IOBuf
*/
class CDebug : public Debug
{
private:
protected:
	Bool put(char);
	Bool doFlush();
public:
};

#endif
