#ifdef SUN
#include <stddef.h>
#endif

#include <string.h>
#include <compare.h>
#include <debug.h>
#include <OpSys.h>
#include <stdio.h>
#include <IoString.h>

void compare(const char* file, int line,const char* one, const char* two)
{
	if (strcmp(one, two) != 0) {
		*(Debug::current) << "File " << file << " Line " << line
				<< "\n";
		*(Debug::current) << "Failed Was [" << one << "] Should Be [" <<
			two << "]\n\r" << flush;
		os.exit(-1);
	}
}
void compare(const char* file, int line,long one, long two)
{
	if (one != two) {
		*(Debug::current) << "File " << file << " Line " << line << "\n";
		*(Debug::current) << "Failed Was [" << one << "] Should Be [" <<
			two << "]\n\r" << flush;
		os.exit(-1);
	}
}
void compare(const char* file, int line,int one, int two)
{
	if (one != two) {
		*(Debug::current) << "File " << file << " Line " << line << "\n";
		*(Debug::current) << "Failed Was [" << one << "] Should Be [" <<
			two << "]\n\r" << flush;
		os.exit(-1);
	}
}
void compare(const char* file, int line, short one, short two)
{
	if (one != two) {
		*(Debug::current) << "File " << file << " Line " << line << "\n";
		*(Debug::current) << "Failed Was [" << one << "] Should Be [" <<
			two << "]\n\r" << flush;
		os.exit(-1);
	}
}
char* doSprintf(const char* str, char* buf, long num)
{
	os.swapOff();
	sprintf(buf, str, num);
	os.swapOn();
	return buf;
}
void compare(const char* file, int line, const char* shouldBe, CmdPipe* output)
{
	char buffer[32], c;
	IOString testStr(buffer, sizeof(buffer));
	do {
		*output >> c;
		testStr << c;
	} while (c != ')');
	compare(file, line, buffer, shouldBe);
}
