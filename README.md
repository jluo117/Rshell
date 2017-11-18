# Assignment 3: Rshell-Pied-Piper

##This program in C++ is designed to be a command shell. The shell performs the following tasks:  
*Prints a command prompt ($)  
*Reads in a command on one line  
*Handles the connectors ||, &&, and ;  
*Executes multiple commands based on the connectors  
*Exits the shell with a built in command  
*Considers anything after a # character a comment  

##In assignment 3, we've enhanced the command shell by adding the test command and parenthesis as precedence operators.

###Test Command  
*returns (TRUE) if it succeeds or (FALSE) if it fails  
*can be executed using the keyword test  

$test -e test/file/path  

*can be executed symbollically by using brackets  

$[ -e test/file/path ]   

*allows the user to run the following flags:  
..*-e to check if a file/directory exists  
..*-d to check if a file/directory exists and is a directory  
..*-f to check if a file/directory exists and is a regular file  
If no flag is specified, the functionality of -e will be used.  

###Precedence Operators  
*used to change the order of the returns of commands, connectors, and chains of connectors  
$ echo 1 && echo 2 || echo 3 && echo 4
prints
1  
2  
4
$(echo 1 && echo 2) || (echo 3 && echo 4)  
prints  
1  
2  

## Current Bugs  
*doesn't echo statements with space between quotation marks and brackets  
$echo " [ test/file/path "]  


[Style guide](https://google.github.io/styleguide/cppguide.html)
