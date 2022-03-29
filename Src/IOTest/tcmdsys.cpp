/*
{inc,copyrite.txt}
*/
/*
  $Revision: 1.1 $
  $Modtime:   12 May 1992 21:34:38  $
  $Workfile:   tcmdsys.cpp  $
*/
#include <CmdTask.h>
#include <CmdHandler.h>
#include <OpSys.h>
#include <debug.h>
#include <CmdSys.h>
void cmdSysOnce()
{
	char pipe1[32], pipe2[32];
	CmdHandler cmdHandler;
	CmdSystem cmdSys(&cmdHandler);
	CmdPipe input(pipe1, elementsof(pipe1), OS_FIFO, "Input");
	CmdPipe output(pipe2, elementsof(pipe2), OS_FIFO, "output");
	CmdTask cmdTask(&cmdHandler, &input, &output);
	*Debug::current << "Print out system information\n";
	input << "(sys,(all))";
	*Debug::current << "Print out task information\n";
	input << "(sys,(tasks))";
	*Debug::current << "Print out block information\n";
	input << "(sys,(blocks))";
}
