/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:14  $
  $Workfile:   IoString.h  $
*/
#ifndef IOSTRING_H
#define IOSTRING_H
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OsTypes.h>
#include <IoBuf.h>
/* 
IOString
Description:
   Parent Class: IOBuf.
   The IOString class implements a string class, supporting all 
   the formatting methods of class IOBuf.
   This class is passed an external character array, and its 
   length. This is the buffer in which all formatting is done and 
   the string is stored. The character data stored in this buffer 
   is always zero terminated. Up to sizeof(buffer) - 1 characters 
   can be stored in the IOString, as one character space is always 
   reserved for the terminating null character.
Usage:

   #include <IoString.h>
   #define IOSTRING_LENGTH ???

   extern char ioStringBuf[IOSTRING_LENGTH];

   IOString ioString(ioStringBuf, sizeof(ioStringBuf));

Data:
   access              Is a semaphore used to limit access to this 
                       object to one task at a time. This is not 
                       used by the user, but is used by the other 
                       IOString methods. This is a priority 
                       semaphore, so that tasks that are waiting 
                       on this semaphore will become unblocked 
                       highest priority task first.
   buffer              Buffer is a pointer to the external 
                       character array where the string characters 
                       are stored.
   length              Length is the number of bytes the external 
                       character array. Up to length - 1 
                       characters can be stored in the IOString.
   front               Front is the next position to write in the 
                       external buffer when IOString::put is 
                       called. Front is incremented each time 
                       IOString::put is called and cleared when 
                       doFlush() is called. Front is never greater 
                       than the length of the array.
   back                Back is the position of the next character 
                       in the external buffer to be read via 
                       IOString::get. Back is incremented with 
                       each get and cleared with each 
                       IOString::doFlush.
Methods:
   IOString::IOString  IOString constructor.
   IOString::put       Put a character onto the buffer[front++].
   IOString::get       Get a character from buffer[back++].
   IOString::strlen    Return # of characters in string.
   IOString::string    Return address of next byte in buffer that 
                       will be returned via IOString::get call. 
                       This will be the address of a null 
                       terminated string of characters.
   IOString::doFlush   is called via the 'IOBuf << flush' 
                       manipulator. It clears all data from the 
                       IOString.
   IOString::putBack   Puts a character back onto the string. This 
                       will only work if a character has been read 
                       from the string already.
*/

class IOString : public IOBuf
{
 private:
 protected:
  Semaphore access;
  char* buffer;
  short length;
  short front;
  short back;
  Bool put(char c);
  Bool get(char*);
  Bool doFlush();
 public:
  IOString(char*, short);
  Bool putBack(char);
  short strlen();
  char* string();
};

#endif
