# To-Do
To-do simply helps create, manage and use to-do lists on command prompt. 

## Commands  
Commands are passed in via command line arguments. If no command is passed, "Todo" is executed.  
  
\# = index, M = message (string of text, can have white space), {x} = x is optional
1. Todo - Prints To-dos
2. Add {#} M - Adds M at index # or at the end of the list of todos
3. Remove # - Removes to-do at #
4. Update # M - Replaces to-do at # with M
5. Edit - Opens the to-do file for editing
6. Done # - Removes a to-do at # and adds it to the finished list
7. Show - Shows finished to-dos  

## Global Flag  
All commands can be prefaced by 'g' or 'G' to indicate the scope of the command (Global or Local)  
 * Global - a global to-do file for general tasks  
 * Local - a file local to the current working directory, for directory specific tasks
 

## To use this
1. Have gcc installed
1. Clone repository
2. Run: run.bat
3. Add path to todo.exe to PATH
