/*
{inc,copyrite.txt}
*/
/*
  $Revision: 1.1 $
  $Modtime:   12 May 1992 21:34:38  $
  $Workfile:   compare.h  $
*/
#include <CmdPipe.h>
extern void compare(const char*, int, const char*, const char*);
extern void compare(const char*, int, long, long);
extern void compare(const char*, int, int, int);
extern void compare(const char*, int, short, short);
extern void compare(const char*, int, const char*, CmdPipe*);
extern char* doSprintf(const char*, char*, long);
