# idleshell
replication of shell (bash) by rkoronen & avegis  

# Parsing
The input string from readline is first split by delimiter '|' while respecting quotations.  
ex. "echo asd | echo zxc"   ->   "echo asd", "echo zxc"  

## Syntax Errors
The entire string is processed for syntax errors and heredocs before passing the string array into execution.  
The string is iterated and compared to a set of strings such as "<<" ">>" "<" ">" "|" and if the previous and current portion of
the string are both syntax strings, we can assume there is a syntax error.  

!!!NOTE: TODO!!!  
Any syntax string should be followed up by a non syntax and non whitespace character to be valid, (except '|')  
A string ending with a pipe char '|' should ask for cmd args in stdin. (?)  

## Expansion
Before a process is created the string handles any expansion of $var.  

ex. ">infile $var>outfile"    ->    ">infile cat -l>outfile"  

## Redirections
The process begins by handling file redirection by looking for syntax "<<" ">>" "<" ">" in the string
and saving the appropriate filename after the syntax.  
After file redirections the string is split by delimiter ' ' while respecting quotations.  
Then the new string array is sorted so that non redirection portions are at the start of the array and
any strings containing redirections are cleaned (free'd or overwritten with 0's) without reallocating new strings or array.  

ex. "<infile" "cat" "arg1>outfile"    ->    "cat" "arg1" NULL  
NOTE: "arg1>outfile" will simply overwrite the ">outfile" portion with 0's and not reallocate the string  

## Builtins
We check our first arg in process structs string array and compare it to defined strings for builtin commands,
then return an enum for the specific builtin command (or 0 if command is not a builtin).  
If the runtime has more than 1 pipe, all the commands are executed in child processes.  
If there are no pipes, handle builtins in the parent and non builtins in a single child.  

## Signals


## Heredoc
 

## History


## Signals

ctrl-d (SIGCLOSE), exits the shell if no task is ongoing
ctrl-c (SIGINT), exits current task and displays a new prompt on a new line
ctrl-\ (SIGQUIT), does nothing

# ISSUES

## MANDATORY 

export var=something
echo bla ble $var bla bla

exports two bla's
var catches something\necho

2nd bla has '\n' in key? somehow prints it with echo $bla


## NON MANDATORY

unset HOME  
cd ~  
should work  

ls |  
should wait for input cmd?  
