/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:20  $
  $Workfile:   Pipe.h  $
*/
#ifndef PIPE_H
#define PIPE_H

#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>

/* 
Pipe
Description:
   Parent Class: Block.
   An object of class Pipe is the primary means that tasks have of 
   passing information between themselves. An object of class Task 
   or Thread can send data to a Pipe, or receive data from a Pipe. 
   An object reading data from a Pipe will be blocked until data 
   is placed onto the Pipe. An object writing data to a Pipe will 
   be blocked until there is room in the Pipe for the data.
   Optional timeouts can specify how long a task should remain 
   blocked waiting to read data from the Pipe.
   Characters, shorts, ints, longs, or pointers to objects can be 
   placed of removed from a Pipe. The sender and the receiver must 
   be sending/receiving the same type of object though. eg. If the 
   receiving task is waiting for a pointer that is 2 bytes long, 
   and a sending task places a character ' ', then a ' ' onto the 
   Pipe, the receiver will get a pointer to an object at location 
   0x2020.
   Internally the Pipe is a circular character buffer, defined 
   externally to the Pipe, by the user, and passed in via the 
   constructor, where data is placed, and 2 counting semaphores 
   that keep track of free and used elements in the Pipe. 2 
   pointers point to the beginning and end of the circular buffer. 
   Tasks blocked on a Pipe can become unblocked in FIFO order, or 
   task priority order (highest priority tasks before lower 
   priority). The user controls this by the flags setting options 
   OS_FIFO, or OS_PRIORITY in the Pipe constructor. Setting the 
   OS_FIFO bit in flags will make this Pipe a FIFO Pipe, and tasks 
   will become unblocked in FIFO order. The task that was blocked 
   first will become unblocked first.
   Setting the OS_PRIORITY bit will make it a priority Pipe. 
   Highest priority tasks will become unblocked before lower 
   priority tasks.
   If both OS_PRIORITY and OS_FIFO are set, then if will be a FIFO 
   Pipe. The default value is OS_FIFO.
Usage:

   #include <Pipe.h>

   #define PIPE_BUFFER_LENGTH ???

   extern char pipeBuffer[PIPE_BUFFER_LENGTH];

   Pipe pipe(pipeBuffer, sizeof(pipeBuffer), OS_FIFO, "Pipe 
                       Name");

Data:
   free                This is a counting Semaphore that keeps 
                       count of the number of free elements in the 
                       pipe. A free element must exist before a 
                       task can place something onto the pipe.
   used                This is a counting Semaphore that counts 
                       the number of used elements on the pipe. A 
                       used element must exist before a task can 
                       remove an element from the pipe.
   back                Back end of pipe. This is where elements 
                       are placed onto the pipe.
   front               Front of the pipe. This is where elements 
                       are removed from the pipe.
   pipeLength          # of elements in pipe (bytes).
   char* pipe          Pointer to pipe circular buffer.
Methods:
   Pipe::Pipe          Constructor. Set up pointers and counting 
                       semaphores.
   Pipe::~Pipe         Destructor.
   Pipe::put           Put an element onto the pipe. The elements 
                       can be a char, short, int, long, or void*. 
                       An optional timeout specifies how long the 
                       placing task will wait for a free element 
                       in the pipe.
   Pipe::putBack       Put an element onto the front of the pipe. 
                       This will be read by the next Pipe::get 
                       call. The elements can be a char, short, 
                       int, long, or void*.
                       An error is returned if there is no room to 
                       put
   the element onto the Pipe.
   Pipe::get           Get an element from the pipe. The elements 
                       can be a char, short, int, long, or void*. 
                       An optional timeout specifies how long the 
                       receiving task will wait for a used element 
                       in the Pipe.
   Pipe::info          Print out information about this Pipe 
                       object to the debug output Pipe.
*/

class Pipe : public Block
{
  friend class OpSys;
  friend class Test;
 protected:
  Semaphore free;
  Semaphore used;
  short back;
  short front;
  short pipeLength;
  char* pipe;
 public:
  Pipe(char*, int length, BFlags = OS_FIFO, const char* = 0);
  ~Pipe();
  void info();
  OSRet put(const void* element, int, OSTime=OS_NOTIMEOUT);
  OSRet put(const char element, OSTime=OS_NOTIMEOUT);
  OSRet put(const short& element, OSTime=OS_NOTIMEOUT);
  OSRet put(const int& element, OSTime=OS_NOTIMEOUT);
  OSRet put(const long& element, OSTime=OS_NOTIMEOUT);
  OSRet putBack(const void* element, int);
  OSRet putBack(const char element);
  OSRet putBack(const short& element);
  OSRet putBack(const int& element);
  OSRet putBack(const long& element);
  OSRet get(void* element, int count, OSTime=OS_NOTIMEOUT);
  OSRet get(short* element, OSTime=OS_NOTIMEOUT);
  OSRet get(int* element, OSTime=OS_NOTIMEOUT);
  OSRet get(long* element, OSTime=OS_NOTIMEOUT);
  OSRet get(char* element, OSTime=OS_NOTIMEOUT);
  short getUsedValue();
  short getFreeValue();
};

/* 
Pipe::getFreeValue
Description:
   Class Pipe.
   getFreeValue() returns the number of free bytes in the pipe. 
   That is the number of bytes of data that can be written to the 
   pipe before it is full.
   This is not the same as the number of data objects that can be 
   written onto the pipe, as a data object can be more than one 
   byte long.
*/
inline short Pipe::getFreeValue()
{
  return(free.value());
}

/* 
Pipe::getUsedValue
Description:
   Class Pipe.
   Return the number of used bytes in the pipe. That is, the 
   number of bytes of data that are waiting to be read. Note that 
   this is not the same as the number of 'data objects' waiting on 
   the pipe, as a long written onto the pipe will be 2 or 4 bytes 
   (depending on the machine).
*/
inline short Pipe::getUsedValue()
{
  return(used.value());
};

#endif
