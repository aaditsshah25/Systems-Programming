# Flash Shell

Flash is a simple shell written in C that accepts commands from the user and runs them. The name "flash" stands for FLAme-SHell.

## Features

- **REPL (Read-Eval-Print Loop):** Flash operates in a loop where it reads a command from the user, evaluates it, runs it, and prints any results.
  
- **Command Types Supported:**
  - **Simple Command Line:** A single program with its command line switches and options.
  - **Background Command Line:** A command line ending with "#" runs the resulting process in the background.
  - **Sequence:** Multiple simple command lines separated by ",".
  - **Pipe:** Two simple command lines separated by "--", where the first acts as the data source and the second as the data sink.

- **Redirection:** Supports redirection of standard input and output using ">" and "<" symbols.

- **Environment Variables:** Supports up to 15 environment variables, each with an uppercase name of up to 16 characters and a value of up to 240 characters. Special variable "?", stores the exit code of the most recently executed command. Includes commands to set (`set`) and get (`get`) environment variables.

## Usage

1. **Compilation:** Compile the shell using a C compiler (e.g., gcc):
gcc flash.c -o flash

2. **Execution:** Run the compiled executable:
./flash

3. **Commands:**
- Enter commands at the prompt and press Enter to execute.
- Use `,` to separate multiple commands in a sequence.
- Use `--` for piping commands.
- Use `set VARIABLE="value"` to set an environment variable.
- Use `get VARIABLE` to get the value of an environment variable.

**Note:** Will also take commands enclosed in quotes.

4. **Exit:** Enter `exit` to exit the shell.


## Limitations

- **Maximum Environment Variables:** The shell supports a maximum of 15 environment variables.
- **Variable Name Length:** Environment variable names are limited to 16 characters.
- **Variable Value Length:** Environment variable values are limited to 240 characters.

## Dependencies

- Standard C libraries (`stdio.h`, `stdlib.h`, etc.)
- POSIX libraries for system calls (`sys/wait.h`, `unistd.h`, etc.)


## Contributors

-**Aadhya:** Wrote the function to parse the command arguments. Also helped with the functions for setting up environment variable
-**Aadit:** Wrote functions to set up environment variables
-**Abhin:** Wrote functions for infile and outfile as well as the function for executing the command line arguments (cmd_execution)

- Whenever we were stuck, we helped each other by meeting regularly and also took help from AI like chatgpt , gemini etc.


## Authors:

Edited By: Aadit Shah & Abhin Jacob
Last Edited: 3/5/24