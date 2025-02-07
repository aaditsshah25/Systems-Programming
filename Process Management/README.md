## First Process README

## Overview
This C program, named First Process, is designed to execute a binary executable file provided on the command line with various options. It allows users to specify the path of the executable, command line options for the executable, and whether to run the process in the background or foreground.

## Usage
    ./my_cmd -e <pathname of an executable> -o "String of command line options of the executable" [-b | -f]

Command Line Options

-e <pathname>: Compulsory option to specify the pathname of the executable file.

-o "<options>": Optional option to provide command line options for the executable.

-b: Run the process in the background.

-f: Run the process in the foreground.

## Notes
Ensure that the binary executable file (my_cmd) exists and has appropriate permissions.

Use quotation marks around command line options if they contain spaces or special characters.

Only one of -b or -f options should be used.

This has been developed by Aadit Shah and Aadhya Dechamma

## Implementation Details
The C program utilizes system calls and library functions to manage processes and handle command line arguments. Here's a brief overview of its functionality:

Parses command line arguments to extract the executable path, options, and execution mode (background/foreground).
Executes the binary executable using execve() system call.

Handles errors during execution, including failures in process creation or execution of the binary.

Retrieves and prints information about the child process, such as its process ID and exit status.