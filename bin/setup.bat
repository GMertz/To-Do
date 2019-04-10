@ECHO off

cd ..\todo-files
:: ADD PROMPTS FOR DELETION OF SOURCE FILES AFTER INSTALATION
:: ADD PATH TO %PATH%, CHECK FOR DUPS, PROMPT FOR OK
:: CHECK IF TODO.EXE EXISTS, PROMPT IF REINSTALL IS DESIRED

::get path to todo-files
for /f %%i in ('cd ') do set TODO_BIN_PATH=%%i

::replace \ with \\ for use in c
set FORMATTED=\"%TODO_BIN_PATH:\=\\%\"

::go to source and compile 
cd ..\source && gcc driver.c util.c ll.c todo.c commands.c -o ..\bin\todo.exe -DGLOBALPATH=%FORMATTED%

:: return to bin
cd ..\bin

echo Finished Compiling