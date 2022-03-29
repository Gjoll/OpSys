echo Compiling %1.CPP into Objs/%1.obj
ccc68k -dccc.opt %1.CPP -o Objs/%1.obj
copy %1.SRC Objs
