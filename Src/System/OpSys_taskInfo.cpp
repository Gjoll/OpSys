/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:32:12  $
  $Workfile:   taskinfo.cpp  $
*/

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OpSys.h>
#include <BitFlag.h>
#include <Pipe.h>
#include <Thread.h>
#include <debug.h>

#define NAME_WIDTH 25
#define ADDRESS_WIDTH 8
#define INT_WIDTH 8
#define SHORT_WIDTH 4
#define MINI_WIDTH 2

/* 
OpSys::taskInfo
Description:
   Class OpSys.
   These are debug routines that print out information about the 
   currently defined tasks. The debug information is written to 
   the debug object.
*/

#ifndef NDEBUG
static char ast[] = "******** ";
static void printHeader(ITask* ptr)
{
	(*Debug::current) << "["
					  << setw(NAME_WIDTH)
					  << ptr->name
					  << "] ";
  (*Debug::current) << setw(ADDRESS_WIDTH)
					<< hex
					<< (long) ptr
					<< " ";
}

void ITask::info()
{
	printHeader(this);
	(*Debug::current) << ast << "**** " << ast << ast
			    << setw(MINI_WIDTH) << priority << " ";
	if (activeList.next != &activeList)
    {
		if (timeList.next != &timeList)
			(*Debug::current) << "Sleep";
		else
			(*Debug::current) << "Active";
	}
	else 
		(*Debug::current)  << "Blocked";
	(*Debug::current) << '\n';
}

void Task::info()
{
	printHeader(this);
	(*Debug::current) << setw(ADDRESS_WIDTH)
						<< (long) stack
						<< " "
						<< setw(SHORT_WIDTH) 
						<< stackLen 
						<< " "
						<< setw(ADDRESS_WIDTH) 
						<< (long) stackPtr; 
	(*Debug::current) << " "
						<< setw(INT_WIDTH) 
						<< stackFree(4096) 
						<< " "
						<< setw(MINI_WIDTH) 
						<< priority << " ";
	if (activeList.next != &activeList)
	{
		if (timeList.next != &timeList)
			(*Debug::current) << "Sleep";
		else
			(*Debug::current) << "Active";
	}
	else 
		(*Debug::current)  << "Blocked";
	(*Debug::current) << '\n';
}

void OpSys::taskInfo()
{
  static char taskMsg[] =
	 "\n Task Name                  Address |-------- Stack (hex) ----------|Pri State\n";
  static char threadMsg[] =
	 "\n Thread Name                Address |-------- Stack (hex) ----------|Pri State\n";
  static char msg1[]=
	   " -------------------------  -------- -Bottom- -Len -Current --Free--\n";
  TaskList* pPtr;
  Bool flag;
  check();
  flag = OSFalse;

  for (pPtr = os.taskList.next; pPtr!=&os.taskList;pPtr = pPtr->next)
	 {
		ITask* tPtr = (Task*) pPtr->task;
		if (flag == OSFalse)
	{
	  (*Debug::current) << taskMsg << msg1;
	  flag = OSTrue;
	}
		tPtr->info();
	 }
  flag = OSFalse;

  for (pPtr = os.taskList.next; pPtr != &os.taskList; pPtr = pPtr->next)
	 if (pPtr->objType == ThreadType)
		{
	Thread* tPtr = (Thread*) pPtr;
	if (flag == OSFalse)
	  {
		 (*Debug::current) << threadMsg << msg1;
		 flag = OSTrue;
	  }
	tPtr->info();
		}
}
#else
void OpSys::taskInfo()
{
}
#endif

