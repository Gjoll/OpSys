/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:02  $
  $Workfile:   CmdHdr.h  $
*/
#ifndef CMDHDR_H
#define CMDHDR_H
#include <Base.h>

/* 
CmdHdr
Description:
   Parent Class: Base.
   Class CmdHdr is the base class for all command processing 
   classes. It defines the circular linked list links used to link 
   command processing objects to their commands. Users will never 
   define objects of class CmdHdr.
*/

class CmdHdr : public Base
{
  friend class CmdHandler;
  friend class Command;
 private:
 protected:
  CmdHdr* next;
  CmdHdr* last;
 public:
  CmdHdr();
  ~CmdHdr();
};

#endif
