del compile.bat
make -n -f makefile local.objs 	> compile.bat
make -n -f makefile lib 	>> compile.bat
make -n -f makefile link	>> compile.bat
compile.bat

