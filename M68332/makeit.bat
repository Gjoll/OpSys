del compile.bat
make -n -f makefile all.objs    > compile.bat
make -n -f makefile lib         >> compile.bat
make -n -f makefile link        >> compile.bat
compile.bat

