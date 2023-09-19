# Pipex

pipex is a 42 school project designed to understand shell redirections and pipes by building them in C. Parent-children processes communication is done by leveraging the shared nature (between processes) of file descriptors to the open file table.

This pipex program takes an input file, execute a command on it, pipes the result to another command which then writes its result to an output file. 

The result should mimic exactly the shell command:

`$ < input_file command1 | command2 > output file`

this include error exit code and messages for every cases.

It is built using the following system functions and system calls `open`, `close`, `read`, `write`,
`dup2`, `execve`, `fork`, `pipe`, `waitpid` 

## Status

Finished 25/07/2023. 

Grade: 100% 

## Usage

Compile with `make`

### Execution

Pipex can handle 2 commands :

```
./pipex input_file command1 command2 output_file
```

this will execute the same as the following shell command :

`$ < input_file command1 | command2 > output_file`

You could test with an input_file containing "Go dance salsa somewhere Christina :)”
