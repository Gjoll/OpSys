CHIP CPU32
SECT code,$101000
ORDER code
ORDER 0
ORDER strings
ORDER const
ORDER ??INITDATA
ORDER ehsftbl
ORDER initfini
ORDER zerovars
ORDER vars
ORDER ioports
ORDER heap
ORDER stack
INITDATA vars
RESMEM $13F000,$1000
LOAD Objs\ENTRY.OBJ  
LOAD Objs\SYS.OBJ  
LOAD Objs\CHECK.OBJ  
LOAD Objs\LINKS.OBJ  
LOAD Objs\SLEEP.OBJ  
LOAD Objs\SLEEP1.OBJ  
LOAD Objs\SWAP.OBJ  
LOAD Objs\TBITFLAG.OBJ  
LOAD Objs\TMAILBOX.OBJ  
LOAD Objs\TMEM.OBJ  
LOAD Objs\TMEMALC.OBJ  
LOAD Objs\TPIPE.OBJ  
LOAD Objs\TSEMAPHO.OBJ  
LOAD Objs\TTHREAD.OBJ
LOAD Objs\TEST.OBJ 
LOAD OPSYS.LIB
LOAD \mcc68k\cpu32\ccc68kab.lib
LOAD \mcc68k\cpu32\mcc68kab.lib
END