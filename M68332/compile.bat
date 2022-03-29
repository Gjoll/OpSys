asm68k -o Objs/ictl_3xx.obj ictl_3xx.asm
del opsys.lib
lib68k < opsys.cmd
lnk68k -c iotest.cmd -F ieee -M -o iotest.iee
lnk68k -c systest.cmd -F ieee -M -o systest.iee
