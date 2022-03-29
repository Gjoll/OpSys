/*
{inc,copyrite.txt}
*/
/*
  $Revision: 1.1 $
  $Modtime:   12 May 1992 21:34:38  $
  $Workfile:   tcmdint.cpp  $
*/
#include <CmdTask.h>
#include <IoString.h>
#include <CmdHandler.h>
#include <CmdInt.h>
#include <OpSys.h>
#include <debug.h>
#include <compare.h>
static char file[] = __FILE__;
static void test1(int start, int count)
{
	int values[3];
	values[0] = 0;
	values[1] = 0;
	values[2] = 0;
	char pipe1[32], pipe2[32];
	static int bounds[] = {-32000, 32000,-32000, 32000,-32000, 32000};
	CmdHandler cmdHandler;
	CmdInt cmd1(values, bounds, elementsof(values), "Test", &cmdHandler);
	CmdPipe input(pipe1, elementsof(pipe1), OS_FIFO, "Input");
	CmdPipe output(pipe2, elementsof(pipe2), OS_FIFO, "output");
	CmdTask cmdTask(&cmdHandler, &input, &output);
	int last = 0;
	while (count--) {
		input << "(Test)";
		{
 			char buffer[32];
			IOString testStr(buffer, sizeof(buffer));
			testStr << "(Test," << last << "," << last
				<< "," << last << ")";
			compare(file, __LINE__, buffer, &output);
		}
		last = start % 32000;
		start += 1;
		input << "(Test," << last
			<< "," << last
			<< "," << last
			<< ")";
		compare(file, __LINE__, "(Test,ok)", &output);
		if ((count % 25) == 0)
			Debug::current->spin();
	}
}
void cmdIntTestOnce()
{
	int values[3];
	values[0] = 0;
	values[1] = 0;
	values[2] = 0;
	char pipe1[32], pipe2[32];
	static int bounds[] = {0, 10, 11, 20, 21, 30};
	CmdHandler cmdHandler;
	CmdInt cmd1(values, bounds, elementsof(values), "Test", &cmdHandler);
	CmdPipe input(pipe1, elementsof(pipe1), OS_FIFO, "Input");
	CmdPipe output(pipe2, elementsof(pipe2), OS_FIFO, "output");
	CmdTask cmd2(&cmdHandler, &input, &output);
	input << "(Test, 0)";
	compare(file, __LINE__, "(Test,badCount)", &output);
	input << "(Test, 0, 11, 21)";
	compare(file, __LINE__, "(Test,ok)", &output);
	input << "(Test, 10, 20, 30)";
	compare(file, __LINE__, "(Test,ok)", &output);
	input << "(Test, 11, 20, 30)";
	compare(file, __LINE__, "(Test,outOfBounds)", &output);
	input << "(Test, 10, 21, 30)";
	compare(file, __LINE__, "(Test,outOfBounds)", &output);
	input << "(Test, 10, 20, 31)";
	compare(file, __LINE__, "(Test,outOfBounds)", &output);
	input << "(Test, 0, 11, 21)";
	input << "(Test)";
	input << "(Test, 1, 12, 22)";
	input << "(Test)";
	compare(file, __LINE__, "(Test,ok)", &output);
	compare(file, __LINE__, "(Test,0,11,21)", &output);
	compare(file, __LINE__, "(Test,ok)", &output);
	compare(file, __LINE__, "(Test,1,12,22)", &output);
}
void cmdIntTest(int start, int count)
{
	test1(start, count);
}
