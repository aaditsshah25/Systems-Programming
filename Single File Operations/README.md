# File Operations README

This repository provides a simple command-line utility for performing various file operations using C programming language. The utility includes functions for creating files, renaming files, deleting files or directories, creating directories and files, appending text or binary data, appending a binary sequence, and outputting file content to the command line.

## Usage

To use the file operations utility, execute the compiled binary with the desired operation and required arguments. See the [File Operations](#file-operations) section for a list of available operations and their usage.

./file_operations <operation> <arguments>

File Operations
1. Create File
Create an empty file at the specified path.
./file_operations create_file <file_path>

2. Rename File
Rename a file from the old name to the new name.

./file_operations rename_file <old_name> <new_name>

3. Delete File or Directory
Delete the specified file or directory.

./file_operations delete_file_or_directory <path>

4. Create Directory and File
Create a directory at the specified path and a file within that directory.

./file_operations create_directory_and_file <directory_path>

5. Append Text or Binary Data
Append text or binary data to the end of a file.

./file_operations append_text <file_path> <data>

6. Append Binary Sequence
Append a binary sequence starting from an odd number to a file.

./file_operations append_binary_sequence <file_path> <start_odd> <num_bytes>

7. Output on Command Line
Read and output the contents of a file to the command line.

./file_operations output_on_cmd <file_path>

## Compilation
Compile the C program using a C compiler, such as gcc.

gcc file_operations.c -o file_operations

## Execution
Execute the compiled binary with the desired operation and required arguments.

./file_operations <operation> <arguments>

## Contributors:
Aadit Shah
Sanjeev Kumar

## Notes:
This program was developed and tested on a GNU/Linux system.
The Makefile uses the gcc compiler. It must be installed on your system.
mysql-server-core-8.0 package is required for perror used in the bash script.