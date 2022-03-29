/*
{inc,copyrite.txt}
*/
/*
  $Revision: 1.1 $
  $Modtime:   12 May 1992 21:34:38  $
  $Workfile:   tcmdsub.cpp  $
*/
#include <CmdTask.h>
#include <IoString.h>
#include <CmdHandler.h>
#include <CmdInt.h>
#include <OpSys.h>
#include <debug.h>
#include <compare.h>
#include <CmdSub.h>
static char file[] = __FILE__;
void cmdSubTest()
{
	static int bounds[] = {0, 100, 0, 100, 0, 100};
	char in1Buf[64], out1Buf[64];
	CmdHandler cmdHan1;
	int val1[3];
	CmdInt cmdInt1(val1, bounds, elementsof(val1), "Test1", &cmdHan1);
	int val2[3];
	CmdInt cmdInt2(val2, bounds, elementsof(val2), "Test2", &cmdHan1);
	int val3[3];
	CmdInt cmdInt3(val3, bounds, elementsof(val3), "Test3", &cmdHan1);
	int val4[3];
	CmdInt cmdInt4(val4, bounds, elementsof(val4), "Test4", &cmdHan1);
	CmdPipe in1(in1Buf, elementsof(in1Buf), OS_FIFO, "Input 1");
	CmdPipe out1(out1Buf, elementsof(out1Buf), OS_FIFO, "output 1");
	CmdTask cmd1(&cmdHan1, &in1, &out1);
	char in2Buf[64], out2Buf[64];
	CmdHandler cmdHan2;
	CmdPipe in2(in2Buf, elementsof(in2Buf), OS_FIFO, "Input 2");
	CmdPipe out2(out2Buf, elementsof(out2Buf), OS_FIFO, "output 2");
	CmdTask cmd2(&cmdHan2, &in2, &out2);
	CmdSub cmdSub(&cmdHan2, &cmdHan1, "Bridge");
	in1 << "(Test1,1,2,3)";
	compare(file, __LINE__, "(Test1,ok)", &out1);
	in1 << "(Test2,2,3,4)";
	compare(file, __LINE__, "(Test2,ok)", &out1);
	in1 << "(Test3,3,4,5)";
	compare(file, __LINE__, "(Test3,ok)", &out1);
	in2 << "(Bridge,(Test1))";
	compare(file, __LINE__, "(Test1,1,2,3)", &out2);
	in2 << "(Bridge,(Test2))";
	compare(file, __LINE__, "(Test2,2,3,4)", &out2);
	in2 << "(Bridge,(Test3))";
	compare(file, __LINE__, "(Test3,3,4,5)", &out2);
	in1 << "(Test1,10,2,3)(Test2,20,3,4)(Test3,30,4,5)";
	in2 << "(Bridge,(Test1))(Bridge,(Test2))(Bridge,(Test3))";
	compare(file, __LINE__, "(Test1,ok)", &out1);
	compare(file, __LINE__, "(Test2,ok)", &out1);
	compare(file, __LINE__, "(Test3,ok)", &out1);
	compare(file, __LINE__, "(Test1,10,2,3)", &out2);
	compare(file, __LINE__, "(Test2,20,3,4)", &out2);
	compare(file, __LINE__, "(Test3,30,4,5)", &out2);
	in1 << "(Test1,11,2,3)(Test2,21,3,4)(Test3,31,4,5)";
	in2 << "(Bridge,(Test1)(Test2)(Test3))";
	compare(file, __LINE__, "(Test1,ok)", &out1);
	compare(file, __LINE__, "(Test2,ok)", &out1);
	compare(file, __LINE__, "(Test3,ok)", &out1);
	compare(file, __LINE__, "(Test1,11,2,3)", &out2);
	compare(file, __LINE__, "(Test2,21,3,4)", &out2);
	compare(file, __LINE__, "(Test3,31,4,5)", &out2);
}
