#
# Borland C++ IDE generated makefile
# Generated 10-Apr-97 at 11:00:09 PM 
#
.AUTODEPEND


#
# Borland C++ tools
#
IMPLIB  = Implib
BCCDOS  = Bcc +BccDos.cfg 
TLINK   = TLink
TLIB    = TLib
TASM    = Tasm
#
# IDE macros
#


#
# Options
#
IDE_LinkFLAGSDOS =  -LF:\BC5\LIB -c -Gm
IDE_BFLAGS = 
CompLocalOptsAtDOS_opsysdlib =  -ml -f
LinkerLocalOptsAtDOS_opsysdlib =  -c -Tde
ResLocalOptsAtDOS_opsysdlib = 
BLocalOptsAtDOS_opsysdlib =  /C /E /P32
CompOptsAt_opsysdlib = $(CompLocalOptsAtDOS_opsysdlib)
CompInheritOptsAt_opsysdlib = -IF:\BC5\INCLUDE;E:\PROJECTS\OPSYS2\INCLUDE;E:\PROJECTS\OPSYS2\BORDOS -DDOS=1;
LinkerInheritOptsAt_opsysdlib = -m
LinkerOptsAt_opsysdlib = $(LinkerLocalOptsAtDOS_opsysdlib)
ResOptsAt_opsysdlib = $(ResLocalOptsAtDOS_opsysdlib)
BOptsAt_opsysdlib = $(BLocalOptsAtDOS_opsysdlib)
CompLocalOptsAtDOS_systestdexe =  -ml -f-
LinkerLocalOptsAtDOS_systestdexe =  -c -Tde
ResLocalOptsAtDOS_systestdexe = 
BLocalOptsAtDOS_systestdexe = 
CompOptsAt_systestdexe = $(CompLocalOptsAtDOS_systestdexe)
CompInheritOptsAt_systestdexe = -IF:\BC5\INCLUDE;..\INCLUDE;..\BORDOS;..\SRC\SYSTEST;..\SRC\IOTEST -DDOS=1;
LinkerInheritOptsAt_systestdexe = -m
LinkerOptsAt_systestdexe = $(LinkerLocalOptsAtDOS_systestdexe)
ResOptsAt_systestdexe = $(ResLocalOptsAtDOS_systestdexe)
BOptsAt_systestdexe = $(BLocalOptsAtDOS_systestdexe)
CompLocalOptsAtDOS_ddbsrcbsystestbcheckdcpp = 
LinkerLocalOptsAtDOS_ddbsrcbsystestbcheckdcpp = 
ResLocalOptsAtDOS_ddbsrcbsystestbcheckdcpp = 
BLocalOptsAtDOS_ddbsrcbsystestbcheckdcpp = 
CompOptsAt_ddbsrcbsystestbcheckdcpp = $(CompOptsAt_systestdexe) $(CompLocalOptsAtDOS_ddbsrcbsystestbcheckdcpp)
CompInheritOptsAt_ddbsrcbsystestbcheckdcpp = -IF:\BC5\INCLUDE;..\INCLUDE;..\BORDOS;..\SRC\SYSTEST;..\SRC\IOTEST -DDOS=1;
LinkerInheritOptsAt_ddbsrcbsystestbcheckdcpp = -m
LinkerOptsAt_ddbsrcbsystestbcheckdcpp = $(LinkerOptsAt_systestdexe) $(LinkerLocalOptsAtDOS_ddbsrcbsystestbcheckdcpp)
ResOptsAt_ddbsrcbsystestbcheckdcpp = $(ResOptsAt_systestdexe) $(ResLocalOptsAtDOS_ddbsrcbsystestbcheckdcpp)
BOptsAt_ddbsrcbsystestbcheckdcpp = $(BOptsAt_systestdexe) $(BLocalOptsAtDOS_ddbsrcbsystestbcheckdcpp)
CompLocalOptsAtDOS_iotestdexe =  -ml -f-
LinkerLocalOptsAtDOS_iotestdexe =  -c -Tde
ResLocalOptsAtDOS_iotestdexe = 
BLocalOptsAtDOS_iotestdexe = 
CompOptsAt_iotestdexe = $(CompLocalOptsAtDOS_iotestdexe)
CompInheritOptsAt_iotestdexe = -IF:\BC5\INCLUDE;..\INCLUDE;..\BORDOS;..\SRC\SYSTEST;..\SRC\IOTEST -DDOS=1;
LinkerInheritOptsAt_iotestdexe = -m
LinkerOptsAt_iotestdexe = $(LinkerLocalOptsAtDOS_iotestdexe)
ResOptsAt_iotestdexe = $(ResLocalOptsAtDOS_iotestdexe)
BOptsAt_iotestdexe = $(BLocalOptsAtDOS_iotestdexe)

#
# Dependency List
#
Dep_OpSys = \
   opsys.lib\
   systest.exe\
   iotest.exe

OpSys : BccDos.cfg $(Dep_OpSys)
  echo MakeNode

Dep_opsysdlib = \
   BIN\pipe_putback_char.obj\
   BIN\thread_thread1.obj\
   BIN\thread_run.obj\
   BIN\tasklist_tasklist.obj\
   BIN\stask_stask.obj\
   BIN\stask_allocstack.obj\
   BIN\semaphore_wait.obj\
   BIN\semaphore_signal.obj\
   BIN\semaphore.obj\
   BIN\pipe_putback_void.obj\
   BIN\pipe_putback_short.obj\
   BIN\pipe_putback_long.obj\
   BIN\pipe_putback_int.obj\
   BIN\thread_thread2.obj\
   BIN\opsys_taskinfo.obj\
   BIN\pipe_put_long.obj\
   BIN\pipe_put_int.obj\
   BIN\pipe_put_char.obj\
   BIN\pipe_put.obj\
   BIN\pipe_pipe.obj\
   BIN\pipe_get_short.obj\
   BIN\pipe_get_long.obj\
   BIN\pipe_get_int.obj\
   BIN\pipe_get_char.obj\
   BIN\pipe_get.obj\
   BIN\pipe_put_short.obj\
   BIN\opsys_blockinfo.obj\
   BIN\opsys_opsys_stack.obj\
   BIN\opsys_opsys_buffer.obj\
   BIN\opsys_opsys.obj\
   BIN\opsys_maintask.obj\
   BIN\opsys_lock.obj\
   BIN\opsys_exitlater.obj\
   BIN\opsys_exit.obj\
   BIN\opsys_doschedule.obj\
   BIN\opsys_clocktick.obj\
   BIN\opsys_check.obj\
   BIN\opsys_schedule.obj\
   BIN\mailbox_get.obj\
   BIN\membuffer_membuffer.obj\
   BIN\membuffer_get.obj\
   BIN\membuffer_doget.obj\
   BIN\memalloc_unlinkfree.obj\
   BIN\memalloc_put.obj\
   BIN\memalloc_memalloc.obj\
   BIN\memalloc_linkfree.obj\
   BIN\memalloc_get.obj\
   BIN\mailbox_put.obj\
   BIN\mailbox_mailbox.obj\
   BIN\membuffer_put.obj\
   BIN\clock_stop.obj\
   BIN\itask_stop.obj\
   BIN\itask_start.obj\
   BIN\itask_stackfree.obj\
   BIN\itask_sleep.obj\
   BIN\itask_setpriority.obj\
   BIN\itask_run.obj\
   BIN\itask_itask.obj\
   BIN\itask_dotimout.obj\
   BIN\itask_dosetpriority.obj\
   BIN\itask_activate.obj\
   BIN\itask_unblockable.obj\
   BIN\assert.obj\
   BIN\clock_clock.obj\
   BIN\block_unblockall.obj\
   BIN\block_dounblockall.obj\
   BIN\block_blocktask.obj\
   BIN\block_block.obj\
   BIN\bitflag_wait.obj\
   BIN\bitflag_signal.obj\
   BIN\bitflag_bitflag.obj\
   BIN\base_checkinit.obj\
   BIN\base_base.obj\
   BIN\clock_start.obj\
   BIN\iobuf_operatorrs_short.obj\
   BIN\iostring_string.obj\
   BIN\iostring_putback.obj\
   BIN\iostring_put.obj\
   BIN\iostring_iostring.obj\
   BIN\iostring_get.obj\
   BIN\iostring_doflush.obj\
   BIN\iobuf_zerofill.obj\
   BIN\iobuf_spacefill.obj\
   BIN\iobuf_skip.obj\
   BIN\iobuf_setw.obj\
   BIN\iobuf_setfill.obj\
   BIN\iobuf_opertorrs_ushort.obj\
   BIN\iobuf_operatorrs_ulong.obj\
   BIN\iobuf_operatorrs_uint.obj\
   BIN\iostring_strlen.obj\
   BIN\iobuf_operatorls_short.obj\
   BIN\iobuf_operatorrs_iomanipint.obj\
   BIN\iobuf_operatorrs_iomanipchar.obj\
   BIN\iobuf_operatorrs_iomanipbool.obj\
   BIN\iobuf_operatorrs_iobuf.obj\
   BIN\iobuf_operatorrs_int.obj\
   BIN\iobuf_operatorrs_char.obj\
   BIN\iobuf_operatorls_ushort.obj\
   BIN\iobuf_operatorls_ulong.obj\
   BIN\iobuf_operatorls_uint.obj\
   BIN\iobuf_operatorls_str.obj\
   BIN\iobuf_operatorrs_long.obj\
   BIN\iobuf_fail.obj\
   BIN\iobuf_operatorls_iomanipint.obj\
   BIN\iobuf_operatorls_iomanipchar.obj\
   BIN\iobuf_operatorls_iomanipbool.obj\
   BIN\iobuf_operatorls_int.obj\
   BIN\iobuf_operatorls_char.obj\
   BIN\iobuf_operatols_iobuf.obj\
   BIN\iobuf_oct.obj\
   BIN\iobuf_iobuf.obj\
   BIN\iobuf_hex.obj\
   BIN\iobuf_flush.obj\
   BIN\iobuf_operatorls_long.obj\
   BIN\cpipe_get.obj\
   BIN\iobuf_endl.obj\
   BIN\iobuf_doskip.obj\
   BIN\iobuf_dosetw.obj\
   BIN\iobuf_dosetfill.obj\
   BIN\iobuf_dec.obj\
   BIN\iobuf_bin.obj\
   BIN\debug_debug.obj\
   BIN\cpipe_putback_str.obj\
   BIN\cpipe_putback_char.obj\
   BIN\cpipe_put.obj\
   BIN\iobuf_ends.obj\
   BIN\cmdpipe_outnestlevel.obj\
   BIN\cpipe_cpipe.obj\
   BIN\command_command.obj\
   BIN\cnvtab.obj\
   BIN\cmdtask_run.obj\
   BIN\cmdtask_cmdtask.obj\
   BIN\cmdsystem_cmdsystem.obj\
   BIN\cmdsub_execute.obj\
   BIN\cmdsub_cmdsub.obj\
   BIN\cmdpipe_putback.obj\
   BIN\cmdpipe_put.obj\
   BIN\cpipe_doflush.obj\
   BIN\cmdhandler_check.obj\
   BIN\cmdpipe_gettokn.obj\
   BIN\cmdpipe_get.obj\
   BIN\cmdpipe_doflush.obj\
   BIN\cmdpipe_cmdpipe.obj\
   BIN\cmdint_execute.obj\
   BIN\cmdint_cmdint.obj\
   BIN\cmdhdr_cmdhdr.obj\
   BIN\cmdhandler_parse.obj\
   BIN\cmdhandler_link.obj\
   BIN\cmdhandler_cmdhandler.obj\
   BIN\cmdpipe_innestlevel.obj\
   BIN\break.obj\
   BIN\rtclock.obj\
   BIN\pcclock.obj\
   BIN\console.obj\
   BIN\config.obj\
   BIN\cdebug.obj\
   BIN\startup.obj

opsys.lib : $(Dep_opsysdlib)
  $(TLIB) $< $(IDE_BFLAGS) $(BOptsAt_opsysdlib) @&&|
 -+BIN\pipe_putback_char.obj &
-+BIN\thread_thread1.obj &
-+BIN\thread_run.obj &
-+BIN\tasklist_tasklist.obj &
-+BIN\stask_stask.obj &
-+BIN\stask_allocstack.obj &
-+BIN\semaphore_wait.obj &
-+BIN\semaphore_signal.obj &
-+BIN\semaphore.obj &
-+BIN\pipe_putback_void.obj &
-+BIN\pipe_putback_short.obj &
-+BIN\pipe_putback_long.obj &
-+BIN\pipe_putback_int.obj &
-+BIN\thread_thread2.obj &
-+BIN\opsys_taskinfo.obj &
-+BIN\pipe_put_long.obj &
-+BIN\pipe_put_int.obj &
-+BIN\pipe_put_char.obj &
-+BIN\pipe_put.obj &
-+BIN\pipe_pipe.obj &
-+BIN\pipe_get_short.obj &
-+BIN\pipe_get_long.obj &
-+BIN\pipe_get_int.obj &
-+BIN\pipe_get_char.obj &
-+BIN\pipe_get.obj &
-+BIN\pipe_put_short.obj &
-+BIN\opsys_blockinfo.obj &
-+BIN\opsys_opsys_stack.obj &
-+BIN\opsys_opsys_buffer.obj &
-+BIN\opsys_opsys.obj &
-+BIN\opsys_maintask.obj &
-+BIN\opsys_lock.obj &
-+BIN\opsys_exitlater.obj &
-+BIN\opsys_exit.obj &
-+BIN\opsys_doschedule.obj &
-+BIN\opsys_clocktick.obj &
-+BIN\opsys_check.obj &
-+BIN\opsys_schedule.obj &
-+BIN\mailbox_get.obj &
-+BIN\membuffer_membuffer.obj &
-+BIN\membuffer_get.obj &
-+BIN\membuffer_doget.obj &
-+BIN\memalloc_unlinkfree.obj &
-+BIN\memalloc_put.obj &
-+BIN\memalloc_memalloc.obj &
-+BIN\memalloc_linkfree.obj &
-+BIN\memalloc_get.obj &
-+BIN\mailbox_put.obj &
-+BIN\mailbox_mailbox.obj &
-+BIN\membuffer_put.obj &
-+BIN\clock_stop.obj &
-+BIN\itask_stop.obj &
-+BIN\itask_start.obj &
-+BIN\itask_stackfree.obj &
-+BIN\itask_sleep.obj &
-+BIN\itask_setpriority.obj &
-+BIN\itask_run.obj &
-+BIN\itask_itask.obj &
-+BIN\itask_dotimout.obj &
-+BIN\itask_dosetpriority.obj &
-+BIN\itask_activate.obj &
-+BIN\itask_unblockable.obj &
-+BIN\assert.obj &
-+BIN\clock_clock.obj &
-+BIN\block_unblockall.obj &
-+BIN\block_dounblockall.obj &
-+BIN\block_blocktask.obj &
-+BIN\block_block.obj &
-+BIN\bitflag_wait.obj &
-+BIN\bitflag_signal.obj &
-+BIN\bitflag_bitflag.obj &
-+BIN\base_checkinit.obj &
-+BIN\base_base.obj &
-+BIN\clock_start.obj &
-+BIN\iobuf_operatorrs_short.obj &
-+BIN\iostring_string.obj &
-+BIN\iostring_putback.obj &
-+BIN\iostring_put.obj &
-+BIN\iostring_iostring.obj &
-+BIN\iostring_get.obj &
-+BIN\iostring_doflush.obj &
-+BIN\iobuf_zerofill.obj &
-+BIN\iobuf_spacefill.obj &
-+BIN\iobuf_skip.obj &
-+BIN\iobuf_setw.obj &
-+BIN\iobuf_setfill.obj &
-+BIN\iobuf_opertorrs_ushort.obj &
-+BIN\iobuf_operatorrs_ulong.obj &
-+BIN\iobuf_operatorrs_uint.obj &
-+BIN\iostring_strlen.obj &
-+BIN\iobuf_operatorls_short.obj &
-+BIN\iobuf_operatorrs_iomanipint.obj &
-+BIN\iobuf_operatorrs_iomanipchar.obj &
-+BIN\iobuf_operatorrs_iomanipbool.obj &
-+BIN\iobuf_operatorrs_iobuf.obj &
-+BIN\iobuf_operatorrs_int.obj &
-+BIN\iobuf_operatorrs_char.obj &
-+BIN\iobuf_operatorls_ushort.obj &
-+BIN\iobuf_operatorls_ulong.obj &
-+BIN\iobuf_operatorls_uint.obj &
-+BIN\iobuf_operatorls_str.obj &
-+BIN\iobuf_operatorrs_long.obj &
-+BIN\iobuf_fail.obj &
-+BIN\iobuf_operatorls_iomanipint.obj &
-+BIN\iobuf_operatorls_iomanipchar.obj &
-+BIN\iobuf_operatorls_iomanipbool.obj &
-+BIN\iobuf_operatorls_int.obj &
-+BIN\iobuf_operatorls_char.obj &
-+BIN\iobuf_operatols_iobuf.obj &
-+BIN\iobuf_oct.obj &
-+BIN\iobuf_iobuf.obj &
-+BIN\iobuf_hex.obj &
-+BIN\iobuf_flush.obj &
-+BIN\iobuf_operatorls_long.obj &
-+BIN\cpipe_get.obj &
-+BIN\iobuf_endl.obj &
-+BIN\iobuf_doskip.obj &
-+BIN\iobuf_dosetw.obj &
-+BIN\iobuf_dosetfill.obj &
-+BIN\iobuf_dec.obj &
-+BIN\iobuf_bin.obj &
-+BIN\debug_debug.obj &
-+BIN\cpipe_putback_str.obj &
-+BIN\cpipe_putback_char.obj &
-+BIN\cpipe_put.obj &
-+BIN\iobuf_ends.obj &
-+BIN\cmdpipe_outnestlevel.obj &
-+BIN\cpipe_cpipe.obj &
-+BIN\command_command.obj &
-+BIN\cnvtab.obj &
-+BIN\cmdtask_run.obj &
-+BIN\cmdtask_cmdtask.obj &
-+BIN\cmdsystem_cmdsystem.obj &
-+BIN\cmdsub_execute.obj &
-+BIN\cmdsub_cmdsub.obj &
-+BIN\cmdpipe_putback.obj &
-+BIN\cmdpipe_put.obj &
-+BIN\cpipe_doflush.obj &
-+BIN\cmdhandler_check.obj &
-+BIN\cmdpipe_gettokn.obj &
-+BIN\cmdpipe_get.obj &
-+BIN\cmdpipe_doflush.obj &
-+BIN\cmdpipe_cmdpipe.obj &
-+BIN\cmdint_execute.obj &
-+BIN\cmdint_cmdint.obj &
-+BIN\cmdhdr_cmdhdr.obj &
-+BIN\cmdhandler_parse.obj &
-+BIN\cmdhandler_link.obj &
-+BIN\cmdhandler_cmdhandler.obj &
-+BIN\cmdpipe_innestlevel.obj &
-+BIN\break.obj &
-+BIN\rtclock.obj &
-+BIN\pcclock.obj &
-+BIN\console.obj &
-+BIN\config.obj &
-+BIN\cdebug.obj &
-+BIN\startup.obj
|

BIN\pipe_putback_char.obj :  ..\src\system\pipe_putback_char.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\pipe_putback_char.cpp
|

BIN\thread_thread1.obj :  ..\src\system\thread_thread1.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\thread_thread1.cpp
|

BIN\thread_run.obj :  ..\src\system\thread_run.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\thread_run.cpp
|

BIN\tasklist_tasklist.obj :  ..\src\system\tasklist_tasklist.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\tasklist_tasklist.cpp
|

BIN\stask_stask.obj :  ..\src\system\stask_stask.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\stask_stask.cpp
|

BIN\stask_allocstack.obj :  ..\src\system\stask_allocstack.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\stask_allocstack.cpp
|

BIN\semaphore_wait.obj :  ..\src\system\semaphore_wait.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\semaphore_wait.cpp
|

BIN\semaphore_signal.obj :  ..\src\system\semaphore_signal.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\semaphore_signal.cpp
|

BIN\semaphore.obj :  ..\src\system\semaphore.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\semaphore.cpp
|

BIN\pipe_putback_void.obj :  ..\src\system\pipe_putback_void.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\pipe_putback_void.cpp
|

BIN\pipe_putback_short.obj :  ..\src\system\pipe_putback_short.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\pipe_putback_short.cpp
|

BIN\pipe_putback_long.obj :  ..\src\system\pipe_putback_long.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\pipe_putback_long.cpp
|

BIN\pipe_putback_int.obj :  ..\src\system\pipe_putback_int.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\pipe_putback_int.cpp
|

BIN\thread_thread2.obj :  ..\src\system\thread_thread2.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\thread_thread2.cpp
|

BIN\opsys_taskinfo.obj :  ..\src\system\opsys_taskinfo.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\opsys_taskinfo.cpp
|

BIN\pipe_put_long.obj :  ..\src\system\pipe_put_long.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\pipe_put_long.cpp
|

BIN\pipe_put_int.obj :  ..\src\system\pipe_put_int.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\pipe_put_int.cpp
|

BIN\pipe_put_char.obj :  ..\src\system\pipe_put_char.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\pipe_put_char.cpp
|

BIN\pipe_put.obj :  ..\src\system\pipe_put.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\pipe_put.cpp
|

BIN\pipe_pipe.obj :  ..\src\system\pipe_pipe.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\pipe_pipe.cpp
|

BIN\pipe_get_short.obj :  ..\src\system\pipe_get_short.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\pipe_get_short.cpp
|

BIN\pipe_get_long.obj :  ..\src\system\pipe_get_long.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\pipe_get_long.cpp
|

BIN\pipe_get_int.obj :  ..\src\system\pipe_get_int.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\pipe_get_int.cpp
|

BIN\pipe_get_char.obj :  ..\src\system\pipe_get_char.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\pipe_get_char.cpp
|

BIN\pipe_get.obj :  ..\src\system\pipe_get.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\pipe_get.cpp
|

BIN\pipe_put_short.obj :  ..\src\system\pipe_put_short.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\pipe_put_short.cpp
|

BIN\opsys_blockinfo.obj :  ..\src\system\opsys_blockinfo.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\opsys_blockinfo.cpp
|

BIN\opsys_opsys_stack.obj :  ..\src\system\opsys_opsys_stack.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\opsys_opsys_stack.cpp
|

BIN\opsys_opsys_buffer.obj :  ..\src\system\opsys_opsys_buffer.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\opsys_opsys_buffer.cpp
|

BIN\opsys_opsys.obj :  ..\src\system\opsys_opsys.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\opsys_opsys.cpp
|

BIN\opsys_maintask.obj :  ..\src\system\opsys_maintask.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\opsys_maintask.cpp
|

BIN\opsys_lock.obj :  ..\src\system\opsys_lock.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\opsys_lock.cpp
|

BIN\opsys_exitlater.obj :  ..\src\system\opsys_exitlater.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\opsys_exitlater.cpp
|

BIN\opsys_exit.obj :  ..\src\system\opsys_exit.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\opsys_exit.cpp
|

BIN\opsys_doschedule.obj :  ..\src\system\opsys_doschedule.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\opsys_doschedule.cpp
|

BIN\opsys_clocktick.obj :  ..\src\system\opsys_clocktick.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\opsys_clocktick.cpp
|

BIN\opsys_check.obj :  ..\src\system\opsys_check.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\opsys_check.cpp
|

BIN\opsys_schedule.obj :  ..\src\system\opsys_schedule.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\opsys_schedule.cpp
|

BIN\mailbox_get.obj :  ..\src\system\mailbox_get.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\mailbox_get.cpp
|

BIN\membuffer_membuffer.obj :  ..\src\system\membuffer_membuffer.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\membuffer_membuffer.cpp
|

BIN\membuffer_get.obj :  ..\src\system\membuffer_get.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\membuffer_get.cpp
|

BIN\membuffer_doget.obj :  ..\src\system\membuffer_doget.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\membuffer_doget.cpp
|

BIN\memalloc_unlinkfree.obj :  ..\src\system\memalloc_unlinkfree.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\memalloc_unlinkfree.cpp
|

BIN\memalloc_put.obj :  ..\src\system\memalloc_put.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\memalloc_put.cpp
|

BIN\memalloc_memalloc.obj :  ..\src\system\memalloc_memalloc.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\memalloc_memalloc.cpp
|

BIN\memalloc_linkfree.obj :  ..\src\system\memalloc_linkfree.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\memalloc_linkfree.cpp
|

BIN\memalloc_get.obj :  ..\src\system\memalloc_get.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\memalloc_get.cpp
|

BIN\mailbox_put.obj :  ..\src\system\mailbox_put.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\mailbox_put.cpp
|

BIN\mailbox_mailbox.obj :  ..\src\system\mailbox_mailbox.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\mailbox_mailbox.cpp
|

BIN\membuffer_put.obj :  ..\src\system\membuffer_put.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\membuffer_put.cpp
|

BIN\clock_stop.obj :  ..\src\system\clock_stop.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\clock_stop.cpp
|

BIN\itask_stop.obj :  ..\src\system\itask_stop.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\itask_stop.cpp
|

BIN\itask_start.obj :  ..\src\system\itask_start.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\itask_start.cpp
|

BIN\itask_stackfree.obj :  ..\src\system\itask_stackfree.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\itask_stackfree.cpp
|

BIN\itask_sleep.obj :  ..\src\system\itask_sleep.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\itask_sleep.cpp
|

BIN\itask_setpriority.obj :  ..\src\system\itask_setpriority.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\itask_setpriority.cpp
|

BIN\itask_run.obj :  ..\src\system\itask_run.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\itask_run.cpp
|

BIN\itask_itask.obj :  ..\src\system\itask_itask.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\itask_itask.cpp
|

BIN\itask_dotimout.obj :  ..\src\system\itask_dotimout.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\itask_dotimout.cpp
|

BIN\itask_dosetpriority.obj :  ..\src\system\itask_dosetpriority.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\itask_dosetpriority.cpp
|

BIN\itask_activate.obj :  ..\src\system\itask_activate.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\itask_activate.cpp
|

BIN\itask_unblockable.obj :  ..\src\system\itask_unblockable.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\itask_unblockable.cpp
|

BIN\assert.obj :  ..\src\system\assert.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\assert.cpp
|

BIN\clock_clock.obj :  ..\src\system\clock_clock.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\clock_clock.cpp
|

BIN\block_unblockall.obj :  ..\src\system\block_unblockall.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\block_unblockall.cpp
|

BIN\block_dounblockall.obj :  ..\src\system\block_dounblockall.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\block_dounblockall.cpp
|

BIN\block_blocktask.obj :  ..\src\system\block_blocktask.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\block_blocktask.cpp
|

BIN\block_block.obj :  ..\src\system\block_block.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\block_block.cpp
|

BIN\bitflag_wait.obj :  ..\src\system\bitflag_wait.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\bitflag_wait.cpp
|

BIN\bitflag_signal.obj :  ..\src\system\bitflag_signal.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\bitflag_signal.cpp
|

BIN\bitflag_bitflag.obj :  ..\src\system\bitflag_bitflag.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\bitflag_bitflag.cpp
|

BIN\base_checkinit.obj :  ..\src\system\base_checkinit.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\base_checkinit.cpp
|

BIN\base_base.obj :  ..\src\system\base_base.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\base_base.cpp
|

BIN\clock_start.obj :  ..\src\system\clock_start.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\system\clock_start.cpp
|

BIN\iobuf_operatorrs_short.obj :  ..\src\io\iobuf_operatorrs_short.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorrs_short.cpp
|

BIN\iostring_string.obj :  ..\src\io\iostring_string.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iostring_string.cpp
|

BIN\iostring_putback.obj :  ..\src\io\iostring_putback.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iostring_putback.cpp
|

BIN\iostring_put.obj :  ..\src\io\iostring_put.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iostring_put.cpp
|

BIN\iostring_iostring.obj :  ..\src\io\iostring_iostring.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iostring_iostring.cpp
|

BIN\iostring_get.obj :  ..\src\io\iostring_get.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iostring_get.cpp
|

BIN\iostring_doflush.obj :  ..\src\io\iostring_doflush.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iostring_doflush.cpp
|

BIN\iobuf_zerofill.obj :  ..\src\io\iobuf_zerofill.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_zerofill.cpp
|

BIN\iobuf_spacefill.obj :  ..\src\io\iobuf_spacefill.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_spacefill.cpp
|

BIN\iobuf_skip.obj :  ..\src\io\iobuf_skip.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_skip.cpp
|

BIN\iobuf_setw.obj :  ..\src\io\iobuf_setw.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_setw.cpp
|

BIN\iobuf_setfill.obj :  ..\src\io\iobuf_setfill.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_setfill.cpp
|

BIN\iobuf_opertorrs_ushort.obj :  ..\src\io\iobuf_opertorrs_ushort.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_opertorrs_ushort.cpp
|

BIN\iobuf_operatorrs_ulong.obj :  ..\src\io\iobuf_operatorrs_ulong.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorrs_ulong.cpp
|

BIN\iobuf_operatorrs_uint.obj :  ..\src\io\iobuf_operatorrs_uint.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorrs_uint.cpp
|

BIN\iostring_strlen.obj :  ..\src\io\iostring_strlen.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iostring_strlen.cpp
|

BIN\iobuf_operatorls_short.obj :  ..\src\io\iobuf_operatorls_short.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorls_short.cpp
|

BIN\iobuf_operatorrs_iomanipint.obj :  ..\src\io\iobuf_operatorrs_iomanipint.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorrs_iomanipint.cpp
|

BIN\iobuf_operatorrs_iomanipchar.obj :  ..\src\io\iobuf_operatorrs_iomanipchar.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorrs_iomanipchar.cpp
|

BIN\iobuf_operatorrs_iomanipbool.obj :  ..\src\io\iobuf_operatorrs_iomanipbool.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorrs_iomanipbool.cpp
|

BIN\iobuf_operatorrs_iobuf.obj :  ..\src\io\iobuf_operatorrs_iobuf.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorrs_iobuf.cpp
|

BIN\iobuf_operatorrs_int.obj :  ..\src\io\iobuf_operatorrs_int.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorrs_int.cpp
|

BIN\iobuf_operatorrs_char.obj :  ..\src\io\iobuf_operatorrs_char.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorrs_char.cpp
|

BIN\iobuf_operatorls_ushort.obj :  ..\src\io\iobuf_operatorls_ushort.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorls_ushort.cpp
|

BIN\iobuf_operatorls_ulong.obj :  ..\src\io\iobuf_operatorls_ulong.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorls_ulong.cpp
|

BIN\iobuf_operatorls_uint.obj :  ..\src\io\iobuf_operatorls_uint.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorls_uint.cpp
|

BIN\iobuf_operatorls_str.obj :  ..\src\io\iobuf_operatorls_str.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorls_str.cpp
|

BIN\iobuf_operatorrs_long.obj :  ..\src\io\iobuf_operatorrs_long.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorrs_long.cpp
|

BIN\iobuf_fail.obj :  ..\src\io\iobuf_fail.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_fail.cpp
|

BIN\iobuf_operatorls_iomanipint.obj :  ..\src\io\iobuf_operatorls_iomanipint.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorls_iomanipint.cpp
|

BIN\iobuf_operatorls_iomanipchar.obj :  ..\src\io\iobuf_operatorls_iomanipchar.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorls_iomanipchar.cpp
|

BIN\iobuf_operatorls_iomanipbool.obj :  ..\src\io\iobuf_operatorls_iomanipbool.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorls_iomanipbool.cpp
|

BIN\iobuf_operatorls_int.obj :  ..\src\io\iobuf_operatorls_int.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorls_int.cpp
|

BIN\iobuf_operatorls_char.obj :  ..\src\io\iobuf_operatorls_char.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorls_char.cpp
|

BIN\iobuf_operatols_iobuf.obj :  ..\src\io\iobuf_operatols_iobuf.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatols_iobuf.cpp
|

BIN\iobuf_oct.obj :  ..\src\io\iobuf_oct.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_oct.cpp
|

BIN\iobuf_iobuf.obj :  ..\src\io\iobuf_iobuf.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_iobuf.cpp
|

BIN\iobuf_hex.obj :  ..\src\io\iobuf_hex.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_hex.cpp
|

BIN\iobuf_flush.obj :  ..\src\io\iobuf_flush.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_flush.cpp
|

BIN\iobuf_operatorls_long.obj :  ..\src\io\iobuf_operatorls_long.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_operatorls_long.cpp
|

BIN\cpipe_get.obj :  ..\src\io\cpipe_get.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cpipe_get.cpp
|

BIN\iobuf_endl.obj :  ..\src\io\iobuf_endl.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_endl.cpp
|

BIN\iobuf_doskip.obj :  ..\src\io\iobuf_doskip.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_doskip.cpp
|

BIN\iobuf_dosetw.obj :  ..\src\io\iobuf_dosetw.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_dosetw.cpp
|

BIN\iobuf_dosetfill.obj :  ..\src\io\iobuf_dosetfill.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_dosetfill.cpp
|

BIN\iobuf_dec.obj :  ..\src\io\iobuf_dec.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_dec.cpp
|

BIN\iobuf_bin.obj :  ..\src\io\iobuf_bin.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_bin.cpp
|

BIN\debug_debug.obj :  ..\src\io\debug_debug.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\debug_debug.cpp
|

BIN\cpipe_putback_str.obj :  ..\src\io\cpipe_putback_str.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cpipe_putback_str.cpp
|

BIN\cpipe_putback_char.obj :  ..\src\io\cpipe_putback_char.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cpipe_putback_char.cpp
|

BIN\cpipe_put.obj :  ..\src\io\cpipe_put.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cpipe_put.cpp
|

BIN\iobuf_ends.obj :  ..\src\io\iobuf_ends.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\iobuf_ends.cpp
|

BIN\cmdpipe_outnestlevel.obj :  ..\src\io\cmdpipe_outnestlevel.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdpipe_outnestlevel.cpp
|

BIN\cpipe_cpipe.obj :  ..\src\io\cpipe_cpipe.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cpipe_cpipe.cpp
|

BIN\command_command.obj :  ..\src\io\command_command.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\command_command.cpp
|

BIN\cnvtab.obj :  ..\src\io\cnvtab.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cnvtab.cpp
|

BIN\cmdtask_run.obj :  ..\src\io\cmdtask_run.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdtask_run.cpp
|

BIN\cmdtask_cmdtask.obj :  ..\src\io\cmdtask_cmdtask.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdtask_cmdtask.cpp
|

BIN\cmdsystem_cmdsystem.obj :  ..\src\io\cmdsystem_cmdsystem.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdsystem_cmdsystem.cpp
|

BIN\cmdsub_execute.obj :  ..\src\io\cmdsub_execute.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdsub_execute.cpp
|

BIN\cmdsub_cmdsub.obj :  ..\src\io\cmdsub_cmdsub.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdsub_cmdsub.cpp
|

BIN\cmdpipe_putback.obj :  ..\src\io\cmdpipe_putback.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdpipe_putback.cpp
|

BIN\cmdpipe_put.obj :  ..\src\io\cmdpipe_put.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdpipe_put.cpp
|

BIN\cpipe_doflush.obj :  ..\src\io\cpipe_doflush.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cpipe_doflush.cpp
|

BIN\cmdhandler_check.obj :  ..\src\io\cmdhandler_check.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdhandler_check.cpp
|

BIN\cmdpipe_gettokn.obj :  ..\src\io\cmdpipe_gettokn.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdpipe_gettokn.cpp
|

BIN\cmdpipe_get.obj :  ..\src\io\cmdpipe_get.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdpipe_get.cpp
|

BIN\cmdpipe_doflush.obj :  ..\src\io\cmdpipe_doflush.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdpipe_doflush.cpp
|

BIN\cmdpipe_cmdpipe.obj :  ..\src\io\cmdpipe_cmdpipe.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdpipe_cmdpipe.cpp
|

BIN\cmdint_execute.obj :  ..\src\io\cmdint_execute.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdint_execute.cpp
|

BIN\cmdint_cmdint.obj :  ..\src\io\cmdint_cmdint.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdint_cmdint.cpp
|

BIN\cmdhdr_cmdhdr.obj :  ..\src\io\cmdhdr_cmdhdr.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdhdr_cmdhdr.cpp
|

BIN\cmdhandler_parse.obj :  ..\src\io\cmdhandler_parse.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdhandler_parse.cpp
|

BIN\cmdhandler_link.obj :  ..\src\io\cmdhandler_link.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdhandler_link.cpp
|

BIN\cmdhandler_cmdhandler.obj :  ..\src\io\cmdhandler_cmdhandler.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdhandler_cmdhandler.cpp
|

BIN\cmdpipe_innestlevel.obj :  ..\src\io\cmdpipe_innestlevel.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ ..\src\io\cmdpipe_innestlevel.cpp
|

BIN\break.obj :  break.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ break.cpp
|

BIN\rtclock.obj :  rtclock.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ rtclock.cpp
|

BIN\pcclock.obj :  pcclock.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ pcclock.cpp
|

BIN\console.obj :  console.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ console.cpp
|

BIN\config.obj :  config.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ config.cpp
|

BIN\cdebug.obj :  cdebug.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ cdebug.cpp
|

BIN\startup.obj :  startup.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_opsysdlib) $(CompInheritOptsAt_opsysdlib) -o$@ startup.cpp
|

Dep_systestdexe = \
   opsys.lib\
   BIN\check.obj\
   BIN\tsemapho.obj\
   BIN\tpipe.obj\
   BIN\tmemalc.obj\
   BIN\tmem.obj\
   BIN\tmailbox.obj\
   BIN\test.obj\
   BIN\tbitflag.obj\
   BIN\swap.obj\
   BIN\sleep1.obj\
   BIN\sleep.obj\
   BIN\links.obj\
   BIN\tthread.obj

systest.exe : $(Dep_systestdexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_systestdexe) $(LinkerInheritOptsAt_systestdexe) +
F:\BC5\LIB\c0l.obj+
BIN\check.obj+
BIN\tsemapho.obj+
BIN\tpipe.obj+
BIN\tmemalc.obj+
BIN\tmem.obj+
BIN\tmailbox.obj+
BIN\test.obj+
BIN\tbitflag.obj+
BIN\swap.obj+
BIN\sleep1.obj+
BIN\sleep.obj+
BIN\links.obj+
BIN\tthread.obj
$<,$*
opsys.lib+
F:\BC5\LIB\cl.lib

|

BIN\check.obj :  ..\src\systest\check.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_ddbsrcbsystestbcheckdcpp) $(CompInheritOptsAt_ddbsrcbsystestbcheckdcpp) -o$@ ..\src\systest\check.cpp
|

BIN\tsemapho.obj :  ..\src\systest\tsemapho.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_systestdexe) $(CompInheritOptsAt_systestdexe) -o$@ ..\src\systest\tsemapho.cpp
|

BIN\tpipe.obj :  ..\src\systest\tpipe.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_systestdexe) $(CompInheritOptsAt_systestdexe) -o$@ ..\src\systest\tpipe.cpp
|

BIN\tmemalc.obj :  ..\src\systest\tmemalc.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_systestdexe) $(CompInheritOptsAt_systestdexe) -o$@ ..\src\systest\tmemalc.cpp
|

BIN\tmem.obj :  ..\src\systest\tmem.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_systestdexe) $(CompInheritOptsAt_systestdexe) -o$@ ..\src\systest\tmem.cpp
|

BIN\tmailbox.obj :  ..\src\systest\tmailbox.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_systestdexe) $(CompInheritOptsAt_systestdexe) -o$@ ..\src\systest\tmailbox.cpp
|

BIN\test.obj :  ..\src\systest\test.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_systestdexe) $(CompInheritOptsAt_systestdexe) -o$@ ..\src\systest\test.cpp
|

BIN\tbitflag.obj :  ..\src\systest\tbitflag.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_systestdexe) $(CompInheritOptsAt_systestdexe) -o$@ ..\src\systest\tbitflag.cpp
|

BIN\swap.obj :  ..\src\systest\swap.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_systestdexe) $(CompInheritOptsAt_systestdexe) -o$@ ..\src\systest\swap.cpp
|

BIN\sleep1.obj :  ..\src\systest\sleep1.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_systestdexe) $(CompInheritOptsAt_systestdexe) -o$@ ..\src\systest\sleep1.cpp
|

BIN\sleep.obj :  ..\src\systest\sleep.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_systestdexe) $(CompInheritOptsAt_systestdexe) -o$@ ..\src\systest\sleep.cpp
|

BIN\links.obj :  ..\src\systest\links.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_systestdexe) $(CompInheritOptsAt_systestdexe) -o$@ ..\src\systest\links.cpp
|

BIN\tthread.obj :  ..\src\systest\tthread.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_systestdexe) $(CompInheritOptsAt_systestdexe) -o$@ ..\src\systest\tthread.cpp
|

Dep_iotestdexe = \
   opsys.lib\
   BIN\compare.obj\
   BIN\tcmdsys.obj\
   BIN\tcmdsub.obj\
   BIN\tcmdint.obj\
   BIN\str2num.obj\
   BIN\num2str.obj\
   BIN\iotest.obj\
   BIN\tiostr.obj

iotest.exe : $(Dep_iotestdexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_iotestdexe) $(LinkerInheritOptsAt_iotestdexe) +
F:\BC5\LIB\c0l.obj+
BIN\compare.obj+
BIN\tcmdsys.obj+
BIN\tcmdsub.obj+
BIN\tcmdint.obj+
BIN\str2num.obj+
BIN\num2str.obj+
BIN\iotest.obj+
BIN\tiostr.obj
$<,$*
opsys.lib+
F:\BC5\LIB\cl.lib

|

BIN\compare.obj :  ..\src\iotest\compare.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_iotestdexe) $(CompInheritOptsAt_iotestdexe) -o$@ ..\src\iotest\compare.cpp
|

BIN\tcmdsys.obj :  ..\src\iotest\tcmdsys.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_iotestdexe) $(CompInheritOptsAt_iotestdexe) -o$@ ..\src\iotest\tcmdsys.cpp
|

BIN\tcmdsub.obj :  ..\src\iotest\tcmdsub.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_iotestdexe) $(CompInheritOptsAt_iotestdexe) -o$@ ..\src\iotest\tcmdsub.cpp
|

BIN\tcmdint.obj :  ..\src\iotest\tcmdint.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_iotestdexe) $(CompInheritOptsAt_iotestdexe) -o$@ ..\src\iotest\tcmdint.cpp
|

BIN\str2num.obj :  ..\src\iotest\str2num.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_iotestdexe) $(CompInheritOptsAt_iotestdexe) -o$@ ..\src\iotest\str2num.cpp
|

BIN\num2str.obj :  ..\src\iotest\num2str.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_iotestdexe) $(CompInheritOptsAt_iotestdexe) -o$@ ..\src\iotest\num2str.cpp
|

BIN\iotest.obj :  ..\src\iotest\iotest.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_iotestdexe) $(CompInheritOptsAt_iotestdexe) -o$@ ..\src\iotest\iotest.cpp
|

BIN\tiostr.obj :  ..\src\iotest\tiostr.cpp
  $(BCCDOS) -c @&&|
 $(CompOptsAt_iotestdexe) $(CompInheritOptsAt_iotestdexe) -o$@ ..\src\iotest\tiostr.cpp
|

# Compiler configuration file
BccDos.cfg : 
   Copy &&|
-W-
-w
-R
-v
-vi
-H
-H=OpSys.csm
-d
-f-
-ff-
-1
-ml
-Og
-Z
-O
-Oe
-Ol
-Ob
-OW
-Oa
-Om
-Op
-Oi
-Ov
| $@


