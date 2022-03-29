/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.


*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:24  $
  $Workfile:   Semaphore.h  $
*/
#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>

/* 
Semaphore
Description:
   Parent Class: Block.
   Each element of Class Semaphore implements a counting semaphore 
   as defined by Dikstra. A Task/Thread can wait for the 
   semaphore, which will cause the task to be blocked until the 
   semaphore is nonzero, whereupon the semaphore will be 
   decremented, or a Task/Thread can signal the semaphore to 
   increment itself.
   Semaphores provide a means of locking access to an object to a 
   specified number of tasks. Setting the initial semaphore count 
   indicates how many tasks can access the object at once.
   Tasks blocked on a semaphore can become unblocked in FIFO 
   order, or task priority order (highest priority tasks before 
   lower priority). The user controls this by the flags setting 
   options OS_FIFO, or OS_PRIORITY in the semaphore constructor. 
   Setting the OS_FIFO bit in flags will make this semaphore a 
   FIFO semaphore, and tasks will become unblocked in FIFO order. 
   The task that was blocked first will become unblocked first.
   Setting the OS_PRIORITY bit will make it a priority semaphore. 
   Highest priority tasks will become unblocked before lower 
   priority tasks.
   If both OS_PRIORITY and OS_FIFO are set, then if will be a FIFO 
   semaphore. The default value is OS_FIFO.
Usage:

   #include <Semaphore.h>

   #define SEMAPHORE_INITIAL_VALUE (int) ???

   Semaphor semaphor(SEMAPHORE_INITIAL_VALUE, OS_FIFO, "Semaphore 
                       Name");

Data:
   signals             Current count of semaphore.
Methods:
   Semaphore::Semaphore    Constructor.
   Semaphore::~Semaphore   Destructor.
   Semaphore::info     Print out information about this Semaphore 
                       object to the debug output pipe.
   Semaphore::intSignal Increment semaphore from interrupt routine.
   						  The semaphore can be incremented by any value,
                       though 1 is the default. Any tasks waiting on
                       the semaphore will be unblocked if the semaphore
                       count is incremented enough to satisfy their
                       request. NO RESCHEDULING IS DONE AT THIS TIME!
   Semaphore::signal   Increment semaphore. The semaphore can be
                       incremented by any value, though 1 is the
                       default. Any tasks waiting on the semaphore
                       will be unblocked if the semaphore count is
                       incremented enough to satisfy their
                       request.
   Semaphore::wait     Wait for semaphore to be greater than or
                       equal the indicated value. The task will be 
                       blocked until that condition is satisfied. 
                       When it is, the task is placed back onto 
                       the active queue and the semaphore is 
                       decremented by the amount the task was 
                       waiting for. An optional timeout value can 
                       specify the max. time that the task will 
                       remain blocked.
   Semaphore::value)   Return current value of signals.
See Also: $/SEE(Block
*/

class Semaphore : public Block
{
  friend class Test;
 protected:
  int signals;
 public:
  Semaphore(int startSigs, BFlags = OS_FIFO, const char* name = 0);
  ~Semaphore();
  void info();
  OSRet intSignal(int signals = 1);
  OSRet signal(int signals = 1);
  OSRet wait(int signals = 1, OSTime=OS_NOTIMEOUT);
  int value();
};

/*
Semaphore::value
Description:
   Class Semaphore.
   Return the current value of the counting semaphore.
*/
inline int Semaphore::value()
{
  return(signals);
}

#endif
