// **************************************************************
/*Copyright 1996 Mark J. Giebler.
This is an unpublished work by Mark J. Giebler. All
rights are reserved, and no part of this work may be
distributed or released with out the express permission
of Mark J. Giebler 23470 Manning Court North, New Scandia, MN  55073-9511
*/
// Class: Interrupt_68K
// Author: Mark Giebler
//
// This class provides control over the 68K CPU's interrupt
// vector table and provides interrupt masking/unmasking methods.
//
// This module makes calls to functions defined in the file
// 	ICTL_3XX.ASM
//
// There must be only one Interrupt_68k object.
// **************************************************************
#include "int_68k.h"
#include <assert.h>

// ----------------------------------
//
// initialize static members
//
// ----------------------------------
short Interrupt_68K::depth = 0;		// to keep track of nested calls
//
// start with interrupt levels off...
// user code must call setOnLevel( 0 ) followed by
// setOffLevel( users level ), then followed by a
// call to interrupt_68k.enableInterrupts( 0 )
//
short Interrupt_68K::onLevel = 7;	// current enable level.
short Interrupt_68K::offLevel = 7;	// current interrupt disable level...

short Interrupt_68K::initFlag = 0;
short Interrupt_68K::outOfScope = 0;

//////////////////////////////////////////////////////////////////
//
// Function: dmyIntHandler()
// Description:
//	Dummy interrupt (exception) handler
//	used for uninitialized vectors
//
// "interrupt" type is used to put RTE instruction in.
//
void interrupt dmyIntHandler( void )
{
  assert( 0 );
}
//
// spurious interrupt handler.
// counts spurious interrupt events.
unsigned long spurious = 0;
void interrupt spuriousIntHandler( void )
{
  spurious++;
}

//////////////////////////////////////////////////////////////////
//
// Constructor: Interrupt_68K
// Description:
//	This is the constructor for the interrupt class.
//	It initializes the next available user vector.
//	It initializes the vectorTableBase to the current VBR.
//	It Gets the current interrupt disable level the CPU is at.
//
// Author: Mark Giebler
//
//////////////////////////////////////////////////////////////////

Interrupt_68K::Interrupt_68K()
{
	nextUserVector = USER_VECTOR_BASE;
	nextTrapVector = TRAP0;
	//
	// set vector table to whatever the current value of VBR is.
	//
	vectorTable = (INTRPT_FUNC *) get_VBR() ;
	//
	// set initFlag
	initFlag = INIT_68K;
	//
	// disable interrupts from the start.  This presets
	// depth to 1.  User must call
	// setEnableLevel( x ) and setDisableLevel( y ) then
	// enableInterrupts() to
	// get things going.
	//
	disableInterrupts();

	// install a spurious interrupt handler...
	//
	setHandler( spuriousIntHandler, SPURIOUS );
}

Interrupt_68K::~Interrupt_68K()
{
	initFlag = 0;
}
//////////////////////////////////////////////////////////////////
//
// Method: setVectorBaseAddress( INTRPT_FUNC address[] )
// Description:
//
//	This method sets the VBR to point to a table provided
//	by the calling function.  It does not copy the existing
//	table to the new location.  The interrupt level is not
//	changed!
//	Calling function should call disableInterrupts()
//	before calling this function.  It should initialize
//	the vectors as needed after this method is called and
//	then enable interrupts with a call to enableInterrupts().
//
// Author: Mark Giebler
//
//////////////////////////////////////////////////////////////////
void Interrupt_68K::setVectorBaseAddress( INTRPT_FUNC *address )
{
	vectorTable = address;
	set_VBR( (long*) address);
}
//////////////////////////////////////////////////////////////////
//
// Method: moveVectorTable( INTRPT_FUNC address[] )
// Description:
//	This method moves the VBR to point to a table provided
//	by the calling function.  It does copy the existing
//	table to the new location.  The interrupt disable level is
//	not changed.
//	The CPU's VBR register is changed after the table is copied
//	to its new home.
//
// Author: Mark Giebler
//
//////////////////////////////////////////////////////////////////
void	Interrupt_68K::moveVectorTable( INTRPT_FUNC *destAddr )
{
	int vec;

	if( initFlag != INIT_68K ){
		outOfScope++;
		return;
	}
	// copy current table to new location.
	//
	for( vec = 0; vec < LAST_VECTOR; vec++)
		destAddr[ vec ] = vectorTable[ vec ];
	//
	// set new location
	setVectorBaseAddress( destAddr );
}
//////////////////////////////////////////////////////////////////
//
// Method: setHandler( VECTOR vector, INTRPT_FUNC i_func )
// Description:
//	This method puts the given interrupt handler function
//	pointer into the vector table at the requested vector.
//	If the vector is out of range, BAD_VECTOR is returned.
//	If succesfull, the requested vector is returned.
//	No check is made as to wether an existing vector is being
//	overwritten.
//
// Author: Mark Giebler
//
//////////////////////////////////////////////////////////////////
VECTOR	Interrupt_68K::setHandler( INTRPT_FUNC i_func,  VECTOR vector )
{
	if( initFlag != INIT_68K ){
		outOfScope++;
		return BAD_VECTOR;
	}

	if( vector <= 0 || vector > LAST_VECTOR )
		return BAD_VECTOR;
	vectorTable[ vector ] = (INTRPT_FUNC) i_func;
	return vector;
}
//////////////////////////////////////////////////////////////////
//
// Method: setHandler( INTRPT_FUNC address[] )
// Description:
//	This method puts the given interrupt handler function
//	into the vector table at the next available user location.
//	If no more locations are available, this returns TABLE_FULL.
//	If function address put into table, the vector the function
//	was placed at is returned.
//
// Author: Mark Giebler
//
//////////////////////////////////////////////////////////////////
VECTOR	Interrupt_68K::setHandler( INTRPT_FUNC i_func )
{
	VECTOR users = nextUserVector;

	if( initFlag != INIT_68K ){
		outOfScope++;
		return BAD_VECTOR;
	}

	if( nextUserVector != TABLE_FULL ){
		vectorTable[users] = (INTRPT_FUNC) i_func;
		nextUserVector += (VECTOR) 1;
		if( nextUserVector > LAST_VECTOR )
			nextUserVector = TABLE_FULL;
	}
	return users;
}
//////////////////////////////////////////////////////////////////
//
// Method: removeHandler( VECTOR vec )
// Description:
//	This method removes the interrupt function at the
//	requested vector location and replaces it with a dummy
//	interrupt handler...
//
//
// Author: Mark Giebler
//
//////////////////////////////////////////////////////////////////
void	Interrupt_68K::removeHandler( VECTOR vec )
{
	setHandler( ((dmyIntHandler)), vec );
}
//////////////////////////////////////////////////////////////////
//
// Method: interruptLevel()
// Description:
//	This method returns the current interrupt disable level
//	that is set in the CPU's SR.
//
// Author: Mark Giebler
//
// moved to inline method
//
//////////////////////////////////////////////////////////////////
//short 	Interrupt_68K::interruptLevel()
//{
//	return ( getIntLevel() );
//}

////////////////////////////////////////////////////////////////////
//
// trap( vec );
//
// This calls the trap exception handler at the requested trap
// vector.
//
//Input:
// 	vec	specifies which trap instruction; range TRAP0 to TRAP15
//		If invalid input, then this is a nop.
//
/////////////////////////////////////////////////////////////////////
void Interrupt_68K::trap( VECTOR vec )
{
	switch( vec )
	{
	case TRAP0:
		trap0();
		break;
	case TRAP1:
		trap1();
		break;
	case TRAP2:
		trap2();
		break;
	case TRAP3:
		trap3();
		break;
	case TRAP4:
		trap4();
		break;
	case TRAP5:
		trap5();
		break;
	case TRAP6:
		trap6();
		break;
	case TRAP7:
		trap7();
		break;
	case TRAP8:
		trap8();
		break;
	case TRAP9:
		trap9();
		break;
	case TRAP10:
		trap10();
		break;
	case TRAP11:
		trap11();
		break;
	case TRAP12:
		trap12();
		break;
	case TRAP13:
		trap13();
		break;
	case TRAP14:
		trap14();
		break;
	case TRAP15:
		trap15();
		break;
	default:
	break;
	}
}
//////////////////////////////////////////////////////////////////
//
// Method: setTrapHandler( VECTOR vector, INTRPT_FUNC i_func )
// Description:
//	This method puts the given interrupt handler function
//	pointer into the vector table at the requested vector.
//	If the vector is out of range, BAD_VECTOR is returned.
//	If succesfull, the requested vector is returned.
//	No check is made as to wether an existing vector is being
//	overwritten.
//
// Author: Mark Giebler
//
//////////////////////////////////////////////////////////////////
VECTOR	Interrupt_68K::setTrapHandler( INTRPT_FUNC i_func,  VECTOR vector )
{
	if( initFlag != INIT_68K ){
		outOfScope++;
		return BAD_VECTOR;
	}

	if( vector < TRAP0 || vector > TRAP15)
		return BAD_VECTOR;
	vectorTable[ vector ] = (INTRPT_FUNC) i_func;
	return vector;
}
//////////////////////////////////////////////////////////////////
//
// Method: setTrapHandler( INTRPT_FUNC address[] )
// Description:
//	This method puts the given interrupt handler function
//	into the vector table at the next available trap location.
//	If no more locations are available, this returns TABLE_FULL.
//	If function address put into table, the vector the function
//	was placed at is returned.
//
// Author: Mark Giebler
//
//////////////////////////////////////////////////////////////////
VECTOR	Interrupt_68K::setTrapHandler( INTRPT_FUNC i_func )
{
	VECTOR users = nextTrapVector;
	if( initFlag != INIT_68K ){
		outOfScope++;
		return BAD_VECTOR;
	}

	if( nextTrapVector != TABLE_FULL ){
		vectorTable[users] = (INTRPT_FUNC) i_func;
		nextTrapVector += (VECTOR) 1;
		if( nextTrapVector > TRAP15 )
			nextTrapVector = TABLE_FULL;
	}
	return users;
}
//////////////////////////////////////////////////////////////////
//
// Method: reserve
// Description:
//	This method reserves a block of vectors.  The block begins on
//  modulo 16 bondary.  (I.E the lower nibble must be 0.)
//
// Input:
//  count   The number of vectors in a block to reserve.
//
// Author: Mark Giebler
//
//////////////////////////////////////////////////////////////////
VECTOR  Interrupt_68K::reserve( int count )
{
	VECTOR users = nextUserVector;
	if( initFlag != INIT_68K ){
		outOfScope++;
		return BAD_VECTOR;
	}

	if( users && 0x0f )
	    users = ( users & (VECTOR) 0x0f0 ) + (VECTOR) 0x010;
    nextUserVector = users + (VECTOR) count;
    return users;
}
