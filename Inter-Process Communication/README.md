
# Interprocess Communication README

### Overview:

This C program facilitates a simple exchange of information between two processes using the `pipe()` call. It takes two command-line arguments: the command line string of the data generator and the command line string of the data consumer. The program uses the "|" pipe symbol to separate the commands, where the data generator produces data and the data consumer consumes it.


### Usage:

Command Line Options:

-g "<generator command>": Specifies the command line string of the data generator.

-c "<consumer command>": Specifies the command line string of the data consumer.


### Implementation Details:

The C program utilizes various system calls and library functions to achieve interprocess communication. Here's a brief overview of its functionality:

- Parses command line arguments to extract the generator and consumer commands.
- Creates a pipe using the `pipe()` system call.
- Uses `fork()` to create two child processes for the generator and consumer.
- Redirects the standard output of the generator to the write end of the pipe and the standard input of the consumer to the read end of the pipe using `dup2()`.
- Executes the generator and consumer commands in their respective child processes using `execvp()`.
- Handles errors during execution, including failures in process creation or execution of the commands.
- Waits for both child processes to finish using `waitpid()`.

### Authors:

Edited By: Aadit Shah & Aadhya Dechamma
Last Edited: 2/4/24
