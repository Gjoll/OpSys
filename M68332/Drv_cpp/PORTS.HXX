// (c) Minnesota Mining and Manufacturing Company (3M) 1990
//	 Created in 1990 as an unpublished copyright work. This
// program and the information contained in it is confidential
// and proprietary to 3M and may not be used, copied, or repro-
// duced without the prior written permission of 3M.
//

// File Name             ports.hxx
// Version Number        1.18
// Date of Last Change   3/20/95

// Module: ports.hxx
// Author: Mark J Giebler
// Summary:
//	This module defines all the hardware addresses used inthe scb
//	needed by the C++ modules.
//	It defines many of the bit patterns that are written to the various
//	registers in the MC68332.  
//	Global hardware semaphores are also declared as extern's here.
//	The systemStatus eventflag is declared as extern here.
//
#ifndef PORTSHXX
#define PORTSHXX

extern "C" void reInitSCC1();	// re-init SCC1 port.
extern "C" void reInitSCC3();	// re-init SCC3 port.

#define MCBASE		0xf00000	// base of configuration registers

#define LCD_CONTROLLER_BASE 0x300000	// base address for the LCD
#define NVRAM_BASE 			0x320000
#define NVRAM_TABLE_BASE	0x32FF00


// *************************************************************
//
// Serial Port Registers
// Author: Mark J Giebler
//
// *************************************************************
#define SCDR	(MCBASE + 0x0ffc0e)	// serial data register
#define SCSR	(MCBASE + 0x0ffc0c)	// serial status
#define SCCR1	(MCBASE + 0x0ffc0a)
//
// bits for the SCCR1 register
// (See section 5.6.3.2 in the 68332 USER'S MANUAL
#define TIE		0x0080
#define TCIE	0x0040
#define RIE		0x0020
#define TE		0x0008
#define RE		0x0004
#define SCCR0	(mcbase + 0x0ffc08)
//
// bits for the SCSR register.
//
#define TDRE	0x0100
#define TC		0x0080
#define RDRF	0x0040
#define OR		0x0008
#define NF		0x0004
#define FE		0x0002
#define PE		0x0001


// *************************************************************
//
// Watchdog Port Registers
//
// *************************************************************
#define SYPCR	(MCBASE + 0x0ffa21)	// system protection control register
#define SWSR	(MCBASE + 0x0ffa27)	// software service register


#include <event.hxx>
#include <semapho.hxx>
#include <bytePort.hxx>

extern "C" void initParallel();

// Ports: The following are the external ports defined for the keypad.

extern Semaphore uartSem;

//
// EventFlags: The following are the external eventFlags defined for the 
// 		keypad.
//
extern EventFlag systemStatus;

#define SYSTEM_READY		0x1		// the one status in systemStatus
									// all tasks (except main and watchDog)
									// wait for systemStatus to be ready.
#define STARTUP_FILM_CLEAR	0x02	// film has been cleared at startup and
									// Transport has passed diagnostics
#define ENABLE_INPUT		0x4		// enable user input when set
#define NVRAM_ERROR			0x20	// set during power up if nvram error
#define NVRAM_TAB_ERR		0x40	// set during power up if error
									// with table nvram
#define START_POLLING_INTERLOCKS	0x200	// to poll interlocks

#endif
