@ECHO off

cd ..\todo-files || (md ..\todo-files && cd ..\todo-files)

::get path to todo-files
for /f %%i in ('cd ') do set TODO_BIN_PATH=%%i

::replace \ with \\ for use in c
set FORMATTED=\"%TODO_BIN_PATH:\=\\%\"

::go to source and compile 
cd ..\source && gcc driver.c util.c ll.c todo.c commands.c -o ..\bin\todo.exe -DGLOBALPATH=%FORMATTED%

:: return to bin
cd ..\bin

echo Finished Compiling