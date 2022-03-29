.SUFFIXES: .asm .cpp
O       = Objs
S       = ../Src
I       = ../Include

SYSTestObjs = \
	$(O)/check.obj \
	$(O)/links.obj \
	$(O)/sleep.obj \
	$(O)/sleep1.obj \
	$(O)/swap.obj \
	$(O)/tbitflag.obj \
	$(O)/test.obj \
	$(O)/tmailbox.obj \
	$(O)/tmem.obj \
	$(O)/tmemalc.obj \
	$(O)/tpipe.obj \
	$(O)/tsemapho.obj \
	$(O)/tthread.obj


IOTestObjs = \
	$(O)/compare.obj \
	$(O)/iotest.obj \
	$(O)/num2str.obj \
	$(O)/str2num.obj \
	$(O)/tcmdint.obj \
	$(O)/tcmdsub.obj \
	$(O)/tcmdsys.obj \
	$(O)/tiostr.obj

M68OBJS = \
	$(O)/sys.obj \
	$(O)/entry.obj \
	$(O)/mclock.obj \
	$(O)/ictl_3xx.obj \
	$(O)/int_68k.obj \
	$(O)/cdebug.obj \
	$(O)/osconfig.obj \
	$(O)/startup.obj \
	$(O)/xrayout.obj

OSOBJS = \
	$(O)/cmdhdr.obj \
	$(O)/cmdsys.obj \
	$(O)/cnvtab.obj \
	$(O)/command.obj \
	$(O)/debug.obj \
	$(O)/acheck.obj \
	$(O)/alink.obj \
	$(O)/aparse.obj \
	$(O)/cmdhndlr.obj \
	$(O)/cmdint.obj \
	$(O)/gexecute.obj \
	$(O)/bdoflush.obj \
	$(O)/bget.obj \
	$(O)/bgettokn.obj \
	$(O)/binnest.obj \
	$(O)/boutnest.obj \
	$(O)/bput.obj \
	$(O)/bputback.obj \
	$(O)/cmdpipe.obj \
	$(O)/cexecute.obj \
	$(O)/cmdsub.obj \
	$(O)/cmdtask.obj \
	$(O)/hrun.obj \
	$(O)/cpipe.obj \
	$(O)/ddoflush.obj \
	$(O)/dget.obj \
	$(O)/dput.obj \
	$(O)/dputbak1.obj \
	$(O)/dputbak2.obj \
	$(O)/ebin.obj \
	$(O)/edec.obj \
	$(O)/edofill.obj \
	$(O)/edosetw.obj \
	$(O)/edoskip.obj \
	$(O)/eendl.obj \
	$(O)/eends.obj \
	$(O)/efail.obj \
	$(O)/eflush.obj \
	$(O)/egchar.obj \
	$(O)/egint.obj \
	$(O)/egiobuf.obj \
	$(O)/egiombol.obj \
	$(O)/egiomchr.obj \
	$(O)/egiomint.obj \
	$(O)/eglong.obj \
	$(O)/egshort.obj \
	$(O)/eguint.obj \
	$(O)/egulong.obj \
	$(O)/egushort.obj \
	$(O)/ehex.obj \
	$(O)/eoct.obj \
	$(O)/epchar.obj \
	$(O)/epint.obj \
	$(O)/epiobuf.obj \
	$(O)/epiombol.obj \
	$(O)/epiomchr.obj \
	$(O)/epiomint.obj \
	$(O)/eplong.obj \
	$(O)/epshort.obj \
	$(O)/epstring.obj \
	$(O)/epulong.obj \
	$(O)/epushort.obj \
	$(O)/esetfill.obj \
	$(O)/esetw.obj \
	$(O)/eskip.obj \
	$(O)/espcfill.obj \
	$(O)/euint.obj \
	$(O)/ezrofill.obj \
	$(O)/iobuf.obj \
	$(O)/fdoflsh.obj \
	$(O)/fget.obj \
	$(O)/fput.obj \
	$(O)/fputback.obj \
	$(O)/fstring.obj \
	$(O)/fstrlen.obj \
	$(O)/iostring.obj \
	$(O)/assert.obj \
	$(O)/tasklist.obj \
	$(O)/base.obj \
	$(O)/checkini.obj \
	$(O)/bitflag.obj \
	$(O)/bwait.obj \
	$(O)/signal.obj \
	$(O)/block.obj \
	$(O)/bloktask.obj \
	$(O)/dunball.obj \
	$(O)/unblkall.obj \
	$(O)/clock.obj \
	$(O)/cstart.obj \
	$(O)/cstop.obj \
	$(O)/mailbox.obj \
	$(O)/mget.obj \
	$(O)/mput.obj \
	$(O)/linkfree.obj \
	$(O)/maget.obj \
	$(O)/maput.obj \
	$(O)/maunlink.obj \
	$(O)/memalloc.obj \
	$(O)/mbdoget.obj \
	$(O)/mbget.obj \
	$(O)/mbput.obj \
	$(O)/membuf.obj \
	$(O)/blkinfo.obj \
	$(O)/clktick.obj \
	$(O)/dosched.obj \
	$(O)/exit.obj \
	$(O)/exitlatr.obj \
	$(O)/lock.obj \
	$(O)/maintsk.obj \
	$(O)/opsys.obj \
	$(O)/buffer.obj \
	$(O)/oscheck.obj \
	$(O)/sched.obj \
	$(O)/tskinfo.obj \
	$(O)/pget.obj \
	$(O)/pgetchar.obj \
	$(O)/pgetint.obj \
	$(O)/pgetlng.obj \
	$(O)/pgetshrt.obj \
	$(O)/pipe.obj \
	$(O)/pput.obj \
	$(O)/pputbak1.obj \
	$(O)/pputbak2.obj \
	$(O)/pputbak3.obj \
	$(O)/pputbak4.obj \
	$(O)/pputbak5.obj \
	$(O)/pputchar.obj \
	$(O)/pputint.obj \
	$(O)/pputlng.obj \
	$(O)/pputshrt.obj \
	$(O)/semap.obj \
	$(O)/ssignal.obj \
	$(O)/swait.obj \
	$(O)/activate.obj \
	$(O)/allcstak.obj \
	$(O)/dosetpri.obj \
	$(O)/dotimout.obj \
	$(O)/setpri.obj \
	$(O)/stakfree.obj \
	$(O)/stask.obj \
	$(O)/task.obj \
	$(O)/trun.obj \
	$(O)/tsleep.obj \
	$(O)/tstart.obj \
	$(O)/tstop.obj \
	$(O)/unblk.obj \
	$(O)/thread1.obj \
	$(O)/thread2.obj \
	$(O)/thrun.obj

LIBOBJS = $(M68OBJS) $(OSOBJS)

IO              = $(S)/Io
SYSTEM          = $(S)/SYSTEM
IOTEST          = $(S)/IOTEST
SYSTEST         = $(S)/SYSTEST

CMDHNDLR        = $(IO)/CMDHNDLR
CMDINT          = $(IO)/CMDINT
CMDPIPE         = $(IO)/CMDPIPE
CMDSUB          = $(IO)/CMDSUB
CMDTASK         = $(IO)/CMDTASK
CPIPE           = $(IO)/CPIPE
IOBUF           = $(IO)/IOBUF
IOSTRING        = $(IO)/IOSTRING

BASE            = $(SYSTEM)/BASE
BITFLAG         = $(SYSTEM)/BITFLAG
BLOCK           = $(SYSTEM)/BLOCK
CLOCK           = $(SYSTEM)/CLOCK
MAILBOX         = $(SYSTEM)/MAILBOX
MEMALLOC        = $(SYSTEM)/MEMALLOC
MEMBUF          = $(SYSTEM)/MEMBUF
OPSYS           = $(SYSTEM)/OPSYS
PIPE            = $(SYSTEM)/PIPE
SEMAP           = $(SYSTEM)/SEMAP
TASK            = $(SYSTEM)/TASK
THREAD          = $(SYSTEM)/THREAD

VPATH =  \
	$(IO);\
	$(CMDHNDLR);\
	$(CMDINT);\
	$(CMDPIPE);\
	$(CMDSUB);\
	$(CMDTASK);\
	$(CPIPE);\
	$(IOBUF);\
	$(IOSTRING);\
	$(SYSTEM);\
	$(BASE);\
	$(BITFLAG);\
	$(BLOCK);\
	$(CLOCK);\
	$(MAILBOX);\
	$(MEMALLOC);\
	$(MEMBUF);\
	$(OPSYS);\
	$(PIPE);\
	$(SEMAP);\
	$(TASK);\
	$(THREAD);\
	$(IOTEST);\
	$(SYSTEST)

$(O)/%.obj: %.cpp
	ccc68k -dccc.opt $< -o $(O)/$(*F).obj
	copy $(*F).SRC $(O)
	del $(*F).SRC

$(O)/%.obj: %.asm
	asm68k -o $(O)/$(*F).obj $<

all: all.objs iotest.s systest.s
local.objs: $(M68OBJS)
all.objs: $(LIBOBJS)
lib:
	del opsys.lib
	lib68k < opsys.cmd

link: iotest.s systest.s
opsys.lib: ${LIBOBJS}
	del opsys.lib
	lib68k < opsys.cmd

systest.s: $(SYSTestObjs)
	lnk68k -c systest.cmd -F ieee -M -o systest.iee

iotest.s: $(IOTestObjs)
	lnk68k -c iotest.cmd -F ieee -M -o iotest.iee

clean:
	-rm $(O)/*.*
	-rm *.bak *~
	-rm *.lib *.exe *.map *.iee *.s

$(O)/check.obj: $(SYSTEST)/check.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(SYSTEST)/test.h

$(O)/links.obj: $(SYSTEST)/links.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(SYSTEST)/test.h

$(O)/sleep.obj: $(SYSTEST)/sleep.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/bitflag.h $(I)/semaphor.h \
	$(I)/pipe.h $(I)/opsys.h $(SYSTEST)/test.h

$(O)/sleep1.obj: $(SYSTEST)/sleep1.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h \
	$(I)/bitflag.h $(I)/thread.h $(SYSTEST)/test.h $(I)/debug.h

$(O)/swap.obj: $(SYSTEST)/swap.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(SYSTEST)/test.h

$(O)/tbitflag.obj: $(SYSTEST)/tbitflag.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/bitflag.h \
	$(SYSTEST)/test.h

$(O)/test.obj: $(SYSTEST)/test.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/thread.h \
	$(SYSTEST)/test.h

$(O)/tmailbox.obj: $(SYSTEST)/tmailbox.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/mailbox.h \
	$(I)/thread.h $(SYSTEST)/test.h $(I)/debug.h

$(O)/tmem.obj: $(SYSTEST)/tmem.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/membuf.h $(I)/pipe.h \
	$(I)/thread.h $(SYSTEST)/test.h $(I)/debug.h

$(O)/tmemalc.obj: $(SYSTEST)/tmemalc.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/membuf.h $(I)/pipe.h \
	$(I)/thread.h $(SYSTEST)/test.h $(I)/debug.h $(I)/memalc.h

$(O)/tpipe.obj: $(SYSTEST)/tpipe.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h \
	$(SYSTEST)/test.h $(I)/debug.h

$(O)/tsemapho.obj: $(SYSTEST)/tsemapho.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(SYSTEST)/test.h \
	$(I)/debug.h

$(O)/tthread.obj: $(SYSTEST)/tthread.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/bitflag.h \
	$(I)/pipe.h $(I)/thread.h $(SYSTEST)/test.h $(I)/clock.h $(I)/debug.h

$(O)/compare.obj: $(IOTEST)/compare.cpp \
	$(IOTEST)/compare.h $(I)/debug.h $(I)/opsys.h \
	$(I)/iostring.h

$(O)/iotest.obj: $(IOTEST)/iotest.cpp osconfig.h $(I)/osassert.h \
	$(I)/base.h $(I)/ptrblock.h $(I)/task.h $(I)/block.h \
	$(I)/semaphor.h $(I)/opsys.h $(I)/thread.h \
	CDEBUG.h MCLOCK.h

$(O)/num2str.obj: $(IOTEST)/num2str.cpp $(I)/iostring.h \
	$(I)/opsys.h $(I)/debug.h $(IOTEST)/compare.h

$(O)/str2num.obj: $(IOTEST)/str2num.cpp $(I)/iostring.h \
	$(I)/opsys.h $(I)/debug.h $(IOTEST)/compare.h

$(O)/tcmdint.obj: $(IOTEST)/tcmdint.cpp $(I)/cmdtask.h \
	$(I)/iostring.h $(I)/cmdhan.h $(I)/cmdint.h $(I)/opsys.h \
	$(I)/debug.h $(IOTEST)/compare.h

$(O)/tcmdsub.obj: $(IOTEST)/tcmdsub.cpp $(I)/cmdtask.h \
	$(I)/iostring.h $(I)/cmdhan.h $(I)/cmdint.h $(I)/opsys.h \
	$(I)/debug.h $(IOTEST)/compare.h $(I)/cmdsub.h

$(O)/tcmdsys.obj: $(IOTEST)/tcmdsys.cpp $(I)/cmdtask.h \
	$(I)/cmdhan.h $(I)/opsys.h $(I)/debug.h $(I)/cmdsys.h

$(O)/tiostr.obj: $(IOTEST)/tiostr.cpp $(I)/iostring.h \
	$(I)/opsys.h $(I)/debug.h $(IOTEST)/compare.h

#
# Library objects....
#
$(O)/cdebug.obj: cdebug.cpp cdebug.h
$(O)/xrayout.obj: xrayout.cpp
$(O)/mclock.obj: mclock.cpp mclock.h int_68k.h
$(O)/osconfig.obj: osconfig.cpp osconfig.h int_68k.h
$(O)/startup.obj: startup.cpp
$(O)/int_68k.obj: int_68k.cpp int_68k.h
$(O)/ictl_3xx.obj: ictl_3xx.asm

$(O)/entry.obj: entry.asm
$(O)/sys.obj: SYS.cpp

$(O)/cmdhdr.obj: $(IO)/cmdhdr.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h $(I)/cmdpipe.h $(I)/cmdhdr.h $(I)/command.h

$(O)/cmdsys.obj: $(S)/Io/cmdsys.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h \
	$(I)/iobuf.h $(I)/cpipe.h $(I)/cmdpipe.h $(I)/command.h \
	$(I)/cmdhan.h $(I)/cmdsub.h $(I)/cmdsys.h

$(O)/cnvtab.obj: $(S)/io/cnvtab.cpp $(I)/iobuf.h

$(O)/command.obj: $(S)/io/command.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/cmdhdr.h \
	$(I)/iobuf.h $(I)/cpipe.h $(I)/cmdpipe.h $(I)/ostypes.h \
	$(I)/cmdhan.h $(I)/command.h

$(O)/debug.obj: $(S)/io/debug.cpp osconfig.h $(I)/osassert.h \
	$(I)/base.h $(I)/ptrblock.h $(I)/task.h $(I)/block.h \
	$(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h $(I)/cpipe.h \
	$(I)/debug.h

$(O)/acheck.obj: $(CMDHNDLR)/acheck.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h $(I)/cmdpipe.h $(I)/cmdhdr.h $(I)/cmdhan.h \
	$(I)/command.h $(I)/ostypes.h

$(O)/alink.obj: $(CMDHNDLR)/alink.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/cmdhdr.h \
	$(I)/iobuf.h $(I)/cpipe.h $(I)/cmdpipe.h $(I)/ostypes.h \
	$(I)/cmdhan.h $(I)/command.h

$(O)/aparse.obj: $(CMDHNDLR)/aparse.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h $(I)/cmdpipe.h $(I)/cmdhdr.h $(I)/ostypes.h $(I)/cmdhan.h

$(O)/cmdhndlr.obj: $(CMDHNDLR)/cmdhndlr.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h $(I)/cmdpipe.h $(I)/cmdhdr.h $(I)/ostypes.h $(I)/cmdhan.h

$(O)/cmdint.obj: $(CMDINT)/cmdint.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h $(I)/cmdpipe.h $(I)/cmdhdr.h $(I)/command.h \
	$(I)/cmdhan.h $(I)/cmdint.h

$(O)/gexecute.obj: $(CMDINT)/gexecute.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h $(I)/cmdpipe.h $(I)/cmdhdr.h $(I)/command.h \
	$(I)/cmdhan.h $(I)/cmdint.h

$(O)/bdoflush.obj: $(CMDPIPE)/bdoflush.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h $(I)/cmdpipe.h $(I)/debug.h

$(O)/bget.obj: $(CMDPIPE)/bget.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h $(I)/cmdpipe.h

$(O)/bgettokn.obj: $(CMDPIPE)/bgettokn.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/iostring.h $(I)/cpipe.h $(I)/cmdpipe.h

$(O)/binnest.obj: $(CMDPIPE)/binnest.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h \
	$(I)/iobuf.h $(I)/cpipe.h $(I)/cmdpipe.h

$(O)/boutnest.obj: $(CMDPIPE)/boutnest.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h \
	$(I)/iobuf.h $(I)/cpipe.h $(I)/cmdpipe.h

$(O)/bput.obj: $(CMDPIPE)/bput.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h $(I)/cmdpipe.h

$(O)/bputback.obj: $(CMDPIPE)/bputback.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h $(I)/cmdpipe.h

$(O)/cmdpipe.obj: $(CMDPIPE)/cmdpipe.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h $(I)/cmdpipe.h

$(O)/cexecute.obj: $(CMDSUB)/cexecute.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h $(I)/cmdpipe.h $(I)/command.h $(I)/cmdhan.h \
	$(I)/cmdsub.h

$(O)/cmdsub.obj: $(CMDSUB)/cmdsub.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h $(I)/cmdpipe.h $(I)/command.h $(I)/cmdhan.h \
	$(I)/cmdsub.h

$(O)/cmdtask.obj: $(CMDTASK)/cmdtask.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h $(I)/cmdhan.h $(I)/cmdtask.h $(I)/cmdhdr.h

$(O)/hrun.obj: $(CMDTASK)/hrun.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h $(I)/cmdhdr.h $(I)/cmdhan.h $(I)/cmdtask.h

$(O)/cpipe.obj: $(CPIPE)/cpipe.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h

$(O)/ddoflush.obj: $(CPIPE)/ddoflush.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h

$(O)/dget.obj: $(CPIPE)/dget.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h

$(O)/dput.obj: $(CPIPE)/dput.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h

$(O)/dputbak1.obj: $(CPIPE)/dputbak1.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h

$(O)/dputbak2.obj: $(CPIPE)/dputbak2.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/pipe.h $(I)/iobuf.h \
	$(I)/cpipe.h

$(O)/ebin.obj: $(IOBUF)/ebin.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/edec.obj: $(IOBUF)/edec.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/edofill.obj: $(IOBUF)/edofill.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/edosetw.obj: $(IOBUF)/edosetw.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/edoskip.obj: $(IOBUF)/edoskip.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/eendl.obj: $(IOBUF)/eendl.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/eends.obj: $(IOBUF)/eends.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/efail.obj: $(IOBUF)/efail.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/eflush.obj: $(IOBUF)/eflush.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/egchar.obj: $(IOBUF)/egchar.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h $(I)/debug.h

$(O)/egint.obj: $(IOBUF)/egint.cpp $(I)/rsigprot.h

$(O)/egiobuf.obj: $(IOBUF)/egiobuf.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/egiombol.obj: $(IOBUF)/egiombol.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/egiomchr.obj: $(IOBUF)/egiomchr.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/egiomint.obj: $(IOBUF)/egiomint.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/eglong.obj: $(IOBUF)/eglong.cpp $(I)/rsigprot.h

$(O)/egshort.obj: $(IOBUF)/egshort.cpp $(I)/rsigprot.h

$(O)/eguint.obj: $(IOBUF)/eguint.cpp $(I)/runsprot.h

$(O)/egulong.obj: $(IOBUF)/egulong.cpp $(I)/runsprot.h

$(O)/egushort.obj: $(IOBUF)/egushort.cpp $(I)/runsprot.h

$(O)/ehex.obj: $(IOBUF)/ehex.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/eoct.obj: $(IOBUF)/eoct.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/epchar.obj: $(IOBUF)/epchar.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/epint.obj: $(IOBUF)/epint.cpp $(I)/wsigprot.h

$(O)/epiobuf.obj: $(IOBUF)/epiobuf.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/epiombol.obj: $(IOBUF)/epiombol.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/epiomchr.obj: $(IOBUF)/epiomchr.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/epiomint.obj: $(IOBUF)/epiomint.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/eplong.obj: $(IOBUF)/eplong.cpp $(I)/wsigprot.h

$(O)/epshort.obj: $(IOBUF)/epshort.cpp $(I)/wsigprot.h

$(O)/epstring.obj: $(IOBUF)/epstring.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/epulong.obj: $(IOBUF)/epulong.cpp $(I)/wunsprot.h

$(O)/epushort.obj: $(IOBUF)/epushort.cpp $(I)/wunsprot.h

$(O)/esetfill.obj: $(IOBUF)/esetfill.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/esetw.obj: $(IOBUF)/esetw.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/eskip.obj: $(IOBUF)/eskip.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/espcfill.obj: $(IOBUF)/espcfill.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/euint.obj: $(IOBUF)/euint.cpp $(I)/wunsprot.h

$(O)/ezrofill.obj: $(IOBUF)/ezrofill.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/iobuf.obj: $(IOBUF)/iobuf.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/iobuf.h

$(O)/fdoflsh.obj: $(IOSTRING)/fdoflsh.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/ostypes.h $(I)/iobuf.h \
	$(I)/iostring.h

$(O)/fget.obj: $(IOSTRING)/fget.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/ostypes.h $(I)/iobuf.h \
	$(I)/iostring.h

$(O)/fput.obj: $(IOSTRING)/fput.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/ostypes.h $(I)/iobuf.h \
	$(I)/iostring.h

$(O)/fputback.obj: $(IOSTRING)/fputback.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/ostypes.h $(I)/iobuf.h \
	$(I)/iostring.h

$(O)/fstring.obj: $(IOSTRING)/fstring.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/ostypes.h \
	$(I)/iobuf.h $(I)/iostring.h

$(O)/fstrlen.obj: $(IOSTRING)/fstrlen.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/ostypes.h \
	$(I)/iobuf.h $(I)/iostring.h

$(O)/iostring.obj: $(IOSTRING)/iostring.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/ostypes.h $(I)/iobuf.h \
	$(I)/iostring.h

$(O)/assert.obj: $(SYSTEM)/assert.cpp osconfig.h \
	$(I)/osassert.h $(I)/debug.h $(I)/opsys.h

$(O)/tasklist.obj: $(SYSTEM)/tasklist.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/task.h

$(O)/base.obj: $(BASE)/base.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/debug.h

$(O)/checkini.obj: $(BASE)/checkini.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/bitflag.obj: $(BITFLAG)/bitflag.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/bitflag.h

$(O)/bwait.obj: $(BITFLAG)/bwait.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/bitflag.h

$(O)/signal.obj: $(BITFLAG)/signal.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/bitflag.h

$(O)/block.obj: $(BLOCK)/block.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/bloktask.obj: $(BLOCK)/bloktask.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/mailbox.h

$(O)/dunball.obj: $(BLOCK)/dunball.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/ostypes.h

$(O)/unblkall.obj: $(BLOCK)/unblkall.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/ostypes.h

$(O)/clock.obj: $(CLOCK)/clock.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/ostypes.h $(I)/clock.h

$(O)/cstart.obj: $(CLOCK)/cstart.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/block.h \
	$(I)/semaphor.h $(I)/opsys.h $(I)/ostypes.h $(I)/clock.h

$(O)/cstop.obj: $(CLOCK)/cstop.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/block.h \
	$(I)/semaphor.h $(I)/opsys.h $(I)/ostypes.h $(I)/clock.h

$(O)/mailbox.obj: $(MAILBOX)/mailbox.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/mailbox.h

$(O)/mget.obj: $(MAILBOX)/mget.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/mailbox.h

$(O)/mput.obj: $(MAILBOX)/mput.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/mailbox.h

$(O)/linkfree.obj: $(MEMALLOC)/linkfree.cpp \
	osconfig.h $(I)/osassert.h $(I)/base.h $(I)/ptrblock.h \
	$(I)/task.h $(I)/block.h $(I)/semaphor.h $(I)/membuf.h \
	$(I)/opsys.h $(I)/memalc.h

$(O)/maget.obj: $(MEMALLOC)/maget.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/membuf.h $(I)/opsys.h \
	$(I)/memalc.h

$(O)/maput.obj: $(MEMALLOC)/maput.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/membuf.h $(I)/opsys.h \
	$(I)/memalc.h

$(O)/maunlink.obj: $(MEMALLOC)/maunlink.cpp \
	osconfig.h $(I)/osassert.h $(I)/base.h $(I)/ptrblock.h \
	$(I)/task.h $(I)/block.h $(I)/semaphor.h $(I)/membuf.h \
	$(I)/opsys.h $(I)/memalc.h

$(O)/memalloc.obj: $(MEMALLOC)/memalloc.cpp \
	osconfig.h $(I)/osassert.h $(I)/base.h $(I)/ptrblock.h \
	$(I)/task.h $(I)/block.h $(I)/semaphor.h $(I)/membuf.h \
	$(I)/opsys.h $(I)/memalc.h

$(O)/mbdoget.obj: $(MEMBUF)/mbdoget.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/membuf.h $(I)/opsys.h

$(O)/mbget.obj: $(MEMBUF)/mbget.cpp osconfig.h $(I)/osassert.h \
	$(I)/base.h $(I)/ptrblock.h $(I)/task.h $(I)/block.h \
	$(I)/semaphor.h $(I)/membuf.h $(I)/opsys.h

$(O)/mbput.obj: $(MEMBUF)/mbput.cpp osconfig.h $(I)/osassert.h \
	$(I)/base.h $(I)/ptrblock.h $(I)/task.h $(I)/block.h \
	$(I)/semaphor.h $(I)/membuf.h $(I)/opsys.h

$(O)/membuf.obj: $(MEMBUF)/membuf.cpp \
	osconfig.h $(I)/osassert.h $(I)/base.h $(I)/ptrblock.h \
	$(I)/task.h $(I)/block.h $(I)/semaphor.h $(I)/membuf.h \
	$(I)/opsys.h

$(O)/blkinfo.obj: $(OPSYS)/blkinfo.cpp \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h osconfig.h \
	$(I)/task.h $(I)/opsys.h $(I)/block.h $(I)/bitflag.h \
	$(I)/semaphor.h $(I)/pipe.h $(I)/debug.h $(I)/ostypes.h

$(O)/clktick.obj: \
	$(OPSYS)/clktick.cpp osconfig.h $(I)/osassert.h \
	$(I)/base.h $(I)/ptrblock.h $(I)/task.h $(I)/block.h \
	$(I)/semaphor.h $(I)/opsys.h $(I)/bitflag.h $(I)/pipe.h \
	$(I)/ostypes.h

$(O)/dosched.obj: $(OPSYS)/dosched.cpp \
	osconfig.h $(I)/osassert.h $(I)/base.h $(I)/ptrblock.h \
	$(I)/task.h $(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/exit.obj: $(OPSYS)/exit.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/exitlatr.obj: $(OPSYS)/exitlatr.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/lock.obj: $(OPSYS)/lock.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/maintsk.obj: $(OPSYS)/maintsk.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/opsys.obj: $(OPSYS)/opsys.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/buffer.obj: $(OPSYS)/buffer.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/oscheck.obj: $(OPSYS)/oscheck.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/debug.h

$(O)/sched.obj: $(OPSYS)/sched.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/bitflag.h $(I)/pipe.h

$(O)/tskinfo.obj: $(OPSYS)/tskinfo.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/bitflag.h \
	$(I)/pipe.h $(I)/thread.h $(I)/debug.h

$(O)/pget.obj: $(PIPE)/pget.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h

$(O)/pgetchar.obj: $(PIPE)/pgetchar.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h

$(O)/pgetint.obj: $(PIPE)/pgetint.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h

$(O)/pgetlng.obj: $(PIPE)/pgetlng.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h

$(O)/pgetshrt.obj: $(PIPE)/pgetshrt.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h

$(O)/pipe.obj: $(PIPE)/pipe.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h

$(O)/pput.obj: $(PIPE)/pput.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h

$(O)/pputbak1.obj: $(PIPE)/pputbak1.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h

$(O)/pputbak2.obj: $(PIPE)/pputbak2.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h

$(O)/pputbak3.obj: $(PIPE)/pputbak3.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h

$(O)/pputbak4.obj: $(PIPE)/pputbak4.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h

$(O)/pputbak5.obj: $(PIPE)/pputbak5.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h

$(O)/pputchar.obj: $(PIPE)/pputchar.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h

$(O)/pputint.obj: $(PIPE)/pputint.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h

$(O)/pputlng.obj: $(PIPE)/pputlng.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h

$(O)/pputshrt.obj: $(PIPE)/pputshrt.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/pipe.h

$(O)/semap.obj: $(SEMAP)/semap.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/ssignal.obj: $(SEMAP)/ssignal.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/ostypes.h

$(O)/swait.obj: $(SEMAP)/swait.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/activate.obj: $(TASK)/activate.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/allcstak.obj: $(TASK)/allcstak.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/semaphor.h $(I)/opsys.h

$(O)/dosetpri.obj: $(TASK)/dosetpri.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/dotimout.obj: $(TASK)/dotimout.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/semaphor.h $(I)/opsys.h

$(O)/setpri.obj: $(TASK)/setpri.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/stakfree.obj: $(TASK)/stakfree.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/stask.obj: $(TASK)/stask.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/task.obj: $(TASK)/task.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/trun.obj: $(TASK)/trun.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/tsleep.obj: $(TASK)/tsleep.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/semaphor.h $(I)/opsys.h

$(O)/tstart.obj: $(TASK)/tstart.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/tstop.obj: $(TASK)/tstop.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/unblk.obj: $(TASK)/unblk.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h

$(O)/thread1.obj: $(THREAD)/thread1.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/thread.h

$(O)/thread2.obj: $(THREAD)/thread2.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/thread.h

$(O)/thrun.obj: $(THREAD)/thrun.cpp osconfig.h \
	$(I)/osassert.h $(I)/base.h $(I)/ptrblock.h $(I)/task.h \
	$(I)/block.h $(I)/semaphor.h $(I)/opsys.h $(I)/thread.h
