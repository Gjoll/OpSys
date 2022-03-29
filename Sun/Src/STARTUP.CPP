/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision:   2.1  $
  $Modtime:   01 May 1993 09:34:26  $
  $Workfile:   startup.cpp  $
*/
#include <osconfig.h>
#include <assert.h>
#include <base.h>
#include <ptrblock.h>
#include <task.h>
#include <block.h>
#include <semaphor.h>
#include <opsys.h>
/* 
Sun::startup
Description:
   Running under UNIX, OpSys::startup() does nothing.
*/
void OpSys::startup()
{
}

/* 
Sun::shutdown
Description:
   Running under UNIX, OpSys::shutdown() does nothing.
*/
void OpSys::shutdown()
{
}

