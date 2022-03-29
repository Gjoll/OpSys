#include <string.h>
/*
  The following functions have breakpoints in xray, which then prints
  the contents of str. Do not place any lines after this comment, as
  the xray breakpoint is done by line number.
  */

char debugDummyChar;

xrayChar(const char c)
{
  debugDummyChar = c;
  return 0;
}

xrayout(char* str)
{
  int outLength = strlen(str);
  for (int i = 0; i < outLength; i++)
    xrayChar(str[i]);
  return 0;
}

