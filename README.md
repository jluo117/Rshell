# Assignment 4: Rshell-Pied-Piper

This program in C++ is designed to be a command shell. The shell from Assignments 2 and 3 perform the following tasks:  
* Prints a command prompt ($)  
* Reads in a command on one line  
* Handles the connectors ||, &&, and ;  
* Executes multiple commands based on the connectors  
* Exits the shell with a built in command  
* Considers anything after a # character a comment  
* Run the test command using the keyword or symbollically by using brackets  
* Change the order of returns of commants, connectors, and chains of connectors with parenthesis as precedence operators

### In assignment 4, we've enhanced the command shell by extending it to handle input redirection, output redirction, and piping

Input Redirection <  
* < redirects the input for a command  
* allows input to come from files

Output redirection > and >>  
* > and >> redirect the output to a file  
* creates file if it doesn't exist, otherwise overwrites (>) or appends (>>) the file  

Piping |
* | allows for chaining of processes and commands  
* sends output of one process or command as input to the next

### Current Bugs  
* For output redirection, our program acts like Zshell if there isn't a pipe
* > and >> redirect outputs to files in between > or >> when they should only direct it to the last file  
In this example, the output of echo hello should only be written to file3:  

``` javascript
$echo hello > file1 > file2 > file3
$cat file1
hello
$cat file2
hello
$cat file3
hello
``` 


[Style guide](https://google.github.io/styleguide/cppguide.html)
