/*
Copyright 1992 Kurt W. Allen.
This is an unpublished work by Kurt W. Allen. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Kurt W. Allen, 3540 43'rd Ave S., Mpls, Mn 55406.
*/
/*
  $Revision: 1.1 $
  $Modtime:   01 May 1993 09:30:12  $
  $Workfile:   IoBuf.h  $
*/
#ifndef IOBUF_H
#define IOBUF_H
#include <OsConfig.h>
#include <OsAssert.h>
#include <Base.h>
#include <ptrBlock.h>
#include <Task.h>
#include <Block.h>
#include <Semaphore.h>
#include <OsTypes.h>
#define MAXDIGITS 14
extern const char cnvTab[16];
/* 
IOBuf
Description:
   Parent Class: Base$.
   An IOBuffer is an object that can have formatted character I/O 
   performed on it. This I/O includes reading/writing single 
   characters, converting numbers to and from digit strings in 
   multiple bases, and using I/O manipulators to define exactly 
   how these operations should be performed.
   IOBuf is a 'pure' class, that is, no objects of this class 
   should be created. Rather, classes should be derived from this 
   class. In particular derived classes must implement the 
   following virtual methods.
   a. doFlush()    called by flush manipulator.
   b. get() get one character
   c. put()    Put one character.
   d. putBack()    Put one character back onto IOBuf. This will be 
      the next character read via IOBuf::get.
Data:
   successFlag         True if previous I/O operation was 
                       successful, False otherwise.
   base                Base used for next integer to digit string 
                       conversion. Base is reset to 10 after each 
                       conversion.
   fill                Fill character.
   width               Set width of next output string. 0 = use 
                       width of output string, nonzero = pad if 
                       output string shorter than width. Use fill 
                       characters to pad.
   skipWhiteSpace      If set skip white space on input of 
                       character data.
Methods:
   IOBuf::IOBuf        Constructor.
   IOBuf::doSetW       Called by setw manipulator to set width of 
                       next output operation.
   IOBuf::doSetFill    Called by setfill, blankfill, and zerofill 
                       manipulators to set fill character used for 
                       padding output.
   IOBuf::doSkip       called by skip manipulator to set 
                       skipWhiteSpace for next input operation.
   IOBuf::hex          Set base to hexadecimal for next conversion 
                       only. After next conversion will reset to 
                       decimal.
   IOBuf::dec          Set base to decimal for all following 
                       output. (manipulator).
   IOBuf::oct          Set base to octal for next conversion only. 
                       After next conversion will default 
                       todecimal. (manipulator).
   IOBuf::bin          Set base to binary for next conversion 
                       only. After next conversion will default to 
                       decimal. (manipulator).
   IOBuf::zeroFill     Set fill character to zero. (manipulator).
   IOBuf::spaceFill    Set fill character to space. (manipulator).
   IOBuf::flush        Flush I/O. (manipulator).
   IOBuf::get          Get one character from IOBuf. This is 
                       private, and only called by other IOBuf 
                       methods.
   IOBuf::put          Put one character onto IOBuf. This is 
                       private, and only called by other IOBuf 
                       methods.
   IOBuf::doFlush      Called by flush manipulator to flush I/O. 
                       This must be defined in any derived 
                       classes.
   IOBuf::operator>>   Remove something from the IOBuf. The 
                       removal can include manipulators, 
                       characters, shorts, ints, and longs. 
                       Shorts, ints, and longs will convert the 
                       digit string to a binary number.
   IOBuf::operator<<   Place something onto IOBuf. This can 
                       include chars, ints, longs, shorts, and 
                       manipulators. All shorts, ints, and longs 
                       will be converted to an ASCII digit string 
                       and then written to the IOBuf.
   IOBuf::putBack      Put data back onto the input stream. The 
                       next get()  will return this data.
   IOBuf::fail         Return True if the last I/O operation 
                       failed.
*/
#define IOMANIPINT IOBuf::IOManipInt
#define IOMANIPCHAR IOBuf::IOManipChar
#define IOMANIPBOOL IOBuf::IOManipBool
//#define IOMANIPINT IOManipInt
//#define IOMANIPCHAR IOManipChar
//#define IOMANIPBOOL IOManipBool

class IOBuf : public Base
{
 public:
  class IOManipInt
    {
    public:
      IOBuf& (*fcn)(IOBuf&, int);
      int val;
      IOManipInt(IOBuf& (*newFcn)(IOBuf&, int), int newVal) :
      fcn(newFcn), val(newVal) { };
    };
  class IOManipChar
    {
    public:
      IOBuf& (*fcn)(IOBuf&, char);
      char val;
      IOManipChar(IOBuf& (*newFcn)(IOBuf&, char), int newVal) :
      fcn(newFcn), val(newVal) { };
    };  
  class IOManipBool
    {
    public:
      IOBuf& (*fcn)(IOBuf&, Bool);
      Bool val;
      IOManipBool(IOBuf& (*newFcn)(IOBuf&, Bool), Bool newVal) :
      fcn(newFcn), val(newVal) { };
    };
  friend IOBuf& doSetW(IOBuf&, int);
  friend IOBuf& doSetFill(IOBuf&, char);
  friend IOBuf& doSkip(IOBuf&, Bool);
  friend IOBuf& hex(IOBuf&);
  friend IOBuf& dec(IOBuf&);
  friend IOBuf& oct(IOBuf&);
  friend IOBuf& bin(IOBuf&);
  friend IOBuf& zeroFill(IOBuf&);
  friend IOBuf& spaceFill(IOBuf&);
  friend IOBuf& flush(IOBuf&);
 private:
 protected:
  Bool successFlag;
  short base;
  char fill;
  short width;
  Bool skipWhiteSpace;
  virtual Bool get(char*) = 0;
  virtual Bool put(char) = 0;
  virtual Bool doFlush() = 0;
 public:
  IOBuf();
  virtual Bool putBack(char) = 0;
  IOBuf& operator>>(IOManipInt);
  IOBuf& operator>>(IOManipBool);
  IOBuf& operator>>(IOManipChar);
  IOBuf& operator<<(IOManipInt);
  IOBuf& operator<<(IOManipBool);
  IOBuf& operator<<(IOManipChar);
  IOBuf& operator>> ( IOBuf& (*f) (IOBuf&) );
  IOBuf& operator<< ( IOBuf& (*f) (IOBuf&) );
  IOBuf& operator>>(char&);
  IOBuf& operator>>(short&);
  IOBuf& operator>>(int&);
  IOBuf& operator>>(long&);
  IOBuf& operator>>(unsigned short&);
  IOBuf& operator>>(unsigned int&);
  IOBuf& operator>>(unsigned long&);
  IOBuf& operator<<(char);
  IOBuf& operator<<(short);
  IOBuf& operator<<(unsigned short);
  IOBuf& operator<<(int);
  IOBuf& operator<<(unsigned int);
  IOBuf& operator<<(long);
  IOBuf& operator<<(unsigned long);
  IOBuf& operator<<(const char*);
  Bool fail();
};
extern IOMANIPINT setw(int);
extern IOMANIPBOOL skip(Bool);
extern IOMANIPINT setFill(int);
extern IOBuf& hex(IOBuf&);
extern IOBuf& dec(IOBuf&);
extern IOBuf& oct(IOBuf&);
extern IOBuf& bin(IOBuf&);
extern IOBuf& zeroFill(IOBuf&);
extern IOBuf& spaceFill(IOBuf&);
extern IOBuf& flush(IOBuf&);
extern IOBuf& endl(IOBuf&);
extern IOBuf& ends(IOBuf&);
#endif
