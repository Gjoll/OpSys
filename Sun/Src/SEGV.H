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
  $Workfile:   segv.h  $
*/
#ifndef SegV_H
#define SegV_H
#include <sys/time.h>
#include <signal.h>
#include <osconfig.h>
#include <ostypes.h>
/* 
SegV
Description:
   This class implements a handler for the SEGV signal.
   When this signal is intercepted, an error message is printed to 
   the debug object and the process exits to the SUN os with an 
   exit code of -1.
Data:
   oldVec              This contains the default signal handler. 
                       It will be restored by the destructor.
Methods:
   SegV                Constructor.
   ~SegV               Destructor.
*/
class SegV
{
private:
	sigvec oldVec;
public:
	SegV();
	~SegV();
};

#endif
