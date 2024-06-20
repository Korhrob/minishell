# idleshell
replication of shell (bash) by rkoronen & avegis

## Parsing
The input string from readline is first split by delimiter '|' while respecting quotations.
ex. "echo asd | echo zxc" -> "echo asd", "echo zxc"

## Syntax Errors
The entire string is processed for syntax errors and heredocs before passing the string array into execution.
The string is iterated and compared to a set of strings such as "<<" ">>" "<" ">" "|", if the previous and current portion of
the string are both a syntax string, we can assume there is a syntax error. 

## Expansion
Before a process is created the string handles any expansion of $s.

## Redirections
The process begins by handling file redirection by looking for syntax "<<" ">>" "<" ">" in the string
and saving the appropriate filename into a struct after the syntax.

NOTE: check bash heredoc and normal redirection behaviour when mixing

After file redirections the string is split by delimiter ' ' while respecting quotations.
Then the new string array is sorted so that non redirection portions are at the start of the array and
any strings containing redirections are cleaned (free'd or overwritten with 0's) without reallocating new strings or array.
ex. "<infile" "cat" "arg1>outfile" -> "cat" "arg1" ""

## Builtins
We check our first arg in process struct string array and compare it to define strings for builtins, then return an enum
for the appropriate builtin command (or -1 if command is not a builtin).

NOTE: TODO!!!
If the runtime has more than 1 pipe, all the commands should be executed in child processes.
Only the last builtin in the pipe should execute.
If there are no pipes, handle builtins in the parent and non builtins in child.