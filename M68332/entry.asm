	      OPT       CASE
              SECTION zerovars,,D
stackTop:	DS.L   128
stackBot:
	      SECTION   code,,C             * CODE SECTION            

	      XDEF 	stackTop
	      XDEF	stackBot
	      XDEF      ENTRY               * ENTRY POINT             
	      XDEF      _ENTRY               * ENTRY POINT             
	      XREF      __main                                        
	      XREF      __initcopy                                    
	      XREF      _main                                    
	      ALIGN     2                                             

_ENTRY:
ENTRY:	      LEA.L     stackBot,SP
	      * CLEAR THE zerovars SECTION
	      LEA.L     .STARTOF.(zerovars),A0          * START OF SECTION
	      MOVE.L    #.SIZEOF.(zerovars),d0          * LENGTH OF THE SECTION
zeroLoop:              
	      CLR.L     (a0)+                           * ZERO TO STACK
	      sub.l     #4,d0
	      cmp.l     #0,d0
	      bgt       zeroLoop

    	      * CLEAR THE vars SECTION
	      LEA.L     .STARTOF.(vars),A0          * START OF SECTION
	      MOVE.L    #.SIZEOF.(vars),d0          * LENGTH OF THE SECTION
zeroLp2:              
	      CLR.L     (a0)+                           * ZERO TO STACK
	      sub.l     #4,d0
	      cmp.l     #0,d0
	      bgt       zeroLp2

	      move	#$2000,SR
	      JSR       __initcopy
	      JSR       _main
	      STOP      #$2700
