// **************************************************************
//
// Class: Interrupt_68K
// Author: Mark Giebler
//
// This class provides control over the 68K CPU's interrupt
// vector table and provides interrupt masking/unmasking.
// There is only one of these objects in a system.
//
// **************************************************************
#ifndef INT_68K_H
#define INT_68K_H

//
// declare assembly language routines this clss calls to interface to
// needed CPU registers.
// These are in the module ictl3xx.src
//
extern "C" long* get_VBR( void );
extern "C" long* set_VBR( long *address );
extern "C" short setIntLevel( short level );
extern "C" short getIntLevel( void );
extern "C" void trap0( void );
extern "C" void trap1( void );
extern "C" void trap2( void );
extern "C" void trap3( void );
extern "C" void trap4( void );
extern "C" void trap5( void );
extern "C" void trap6( void );
extern "C" void trap7( void );
extern "C" void trap8( void );
extern "C" void trap9( void );
extern "C" void trap10( void );
extern "C" void trap11( void );
extern "C" void trap12( void );
extern "C" void trap13( void );
extern "C" void trap14( void );
extern "C" void trap15( void );

#define INIT_68K (0x7a25)

//
// following needed when testing compile with symantec C++ comipler...
//
//#ifndef interrupt
//#define interrupt
//#endif
//
// typedef a pointer to an interrupt handle function
//
typedef void interrupt (*INTRPT_FUNC)(void);
//
// enumeration of the 68K's defined vectors in the Vector table.
//
// for a complete decription of all vectors see table 6-1 in
// the CPU32 reference manual.
//
enum VECTOR {
	RESET_STACK,
	RESET_PC,
	BUS_ERR,		// bus error
	ADDR_ERR,
	ILL_INSTRUCT,
	DIV_ZERO,		// divide by zero
	CHK,			//CHK2 instruction vector
	TRAPV,			//TRAPV instruction
	PRIV_VIOLATE,	// privilege violation
	TRACE,			// emulator trace
	L1010,			//
	L1111,			//
	HW_BRKPT,		// hardware break point.
	CP_VIOL,		// coprocessor violation
	UN_INT_1,		// uninitialized interrupt 1
	UN_INT_2,		// vec=15
// **********************************************
// skip 16-23 reserved by motorola, do not use!!
// **********************************************
	SPURIOUS = 24,		// spurious interrupt
	LEVEL1,			// level 1 auto vector interrupt
	LEVEL2,
	LEVEL3,
	LEVEL4,
	LEVEL5,
	LEVEL6,
	LEVEL7,

	TRAP0,			// Trap 0 instruction
	TRAP1,
	TRAP2,
	TRAP3,
	TRAP4,
	TRAP5,
	TRAP6,
	TRAP7,
	TRAP8,
	TRAP9,
	TRAP10,
	TRAP11,
	TRAP12,
	TRAP13,
	TRAP14,
	TRAP15,
// ***********************************************************
// 48 to 63 unassigned and reserved by Motorola, do not use!
// ***********************************************************
	USER_VECTOR_BASE = 64,	// start of user available vectors.
	LAST_VECTOR	= 255,	// last vector available.
	TABLE_FULL	= -1,
	BAD_VECTOR	= -2
};
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
// a user defined vector table should be declared as follows:
// INTRPT_FUNC vectorTable[ LAST_VECTOR ];
//
//
//  Class: Interrupt_68K
// Author: Mark j Giebler
//
class Interrupt_68K {
public:
	Interrupt_68K();
	~Interrupt_68K();
	void	setVectorBaseAddress( INTRPT_FUNC *address );
	void	moveVectorTable( INTRPT_FUNC *destAddr );

	VECTOR	setHandler( INTRPT_FUNC i_func,  VECTOR vector );
	VECTOR	setHandler( INTRPT_FUNC i_func );
	VECTOR	setTrapHandler( INTRPT_FUNC i_func, VECTOR vector );
	VECTOR	setTrapHandler( INTRPT_FUNC i_func );
	VECTOR  reserve( int count );
	void	removeHandler( VECTOR vec );

	void	setDisableLevel( short level );
	void	setEnableLevel( short level );
	void	disableInterrupts(  );
	void	enableInterrupts(  );
	short 	interruptLevel() { return ( getIntLevel() );} ;

	void 	lock() { depth++; };	// increase lock level
	void	unlock() {depth--; };

	void	trap( VECTOR vec );

private:
	VECTOR nextUserVector;	// next user vector table entry available.
	VECTOR nextTrapVector;	// next trap vector available...
	INTRPT_FUNC *vectorTable; // pointer to this objects vector table.
	                            // An array of interrupt function pointers
	static short onLevel;		// current enable level.
	static short offLevel;		// current interrupt disable level...
	static short depth;			// to keep track of nested calls
	static short initFlag;		// to tell if constructor was called.
	static short outOfScope;	// count of how many times methods
								// were called before constructor.
};
//
// setEnableLevel
//
// Used to set the lowest level of interrupts to be on.
// User calls this when all interrupt routines are installed
// that need to be installed.  Must be called after the
// instantiation of the interrupt_68k object at the very least.
//
// Input:
//	level	 the lowest interrupt level to enable.  Range 0 to 7.
//
// Author: Mark J Giebler
inline void	Interrupt_68K::setEnableLevel( short level )
{ onLevel = level;
}

//
// setDisableLevel
//
// Used to set the maximum disable level of the user code when
// the code is in critical areas.
// Must be called after the instantiation of the interrupt_68k
// object.
//
// Input:
//	level	the maximum disable level to use when code is in critical
//		 areas.
//
// Author: Mark J Giebler
//
inline	void	Interrupt_68K::setDisableLevel( short level )
{ offLevel = level;
}


//
// declare the one interrupt object...
// The user must instantiate this object.  It must be before
// any OS objects.
extern Interrupt_68K interrupt_68k;

#ifndef TPU_HXX

#include <tpu_dio.hxx>
extern TPU_DIO pp_hostClockTPU;	/* TPU DIO object that handles strobe */
extern TPU_DIO pp_1284ActiveTPU;
extern TPU_DIO pp_hostAckTPU;
extern TPU_DIO pp_nReverseReqTPU;

//////////////////////////////////////////////////////////////////
//
// Method: disableInterrupts( int level = 7 )
// Description:
//	This method sets the interrupt disable level to
//	the current off level setting.
//
//	Returns: nothing
//
//	level = 0 is all interrupts enabled.
//  level = 6 level 6 and below disabled.
//	level = 7 is all interrupts disabled except level 7 (NMI)
//
//
// Author: Mark Giebler
//
//////////////////////////////////////////////////////////////////
inline void Interrupt_68K::disableInterrupts(  )
{
	setIntLevel( offLevel );
	pp_hostClockTPU.maskInterrupt();
	pp_1284ActiveTPU.maskInterrupt();
	pp_hostAckTPU.maskInterrupt();
	pp_nReverseReqTPU.maskInterrupt();

	depth++;
}
//////////////////////////////////////////////////////////////////
//
// Method: enableInterrupts( int level = 0 )
// Description:
//	This method enables interrupts to the current on level setting.
//  only if all nesting is completed will this change the level.
//
// Author: Mark Giebler
//
//////////////////////////////////////////////////////////////////
inline void	Interrupt_68K::enableInterrupts(  )
{
	depth--;
	if( depth <= 0 )
	  {
	    pp_hostClockTPU.unmaskInterrupt();
	    pp_1284ActiveTPU.unmaskInterrupt();
	    pp_hostAckTPU.unmaskInterrupt();
	    pp_nReverseReqTPU.unmaskInterrupt();
	    setIntLevel( onLevel );
	  }
}
#endif


#endif
