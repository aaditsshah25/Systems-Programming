## Bulk File System Operations
This Command Line Interface (CLI) tool allows users to perform various file system operations, including creating files or directories, appending data, deleting files or directories, renaming, and generating log files.

## Usage
1. Create File or Directory
./file_manager -c <new_name>
Creates a new file or directory with the specified name.

2. Append Text or Binary Data
./file_manager -s "The 50 Byte String" <file_path>
./file_manager -e <starting_even_number> <file_path>
Appends 50 bytes of text or a sequence of even numbers (between 51 and 199) to the specified file.

3. Delete File or Directory
./file_manager -d <file_or_dir_name>
Deletes the specified file or an empty directory. Non-empty directories are deleted after removing all the files contained within.

4. Rename File or Directory
./file_manager -r <old_name> <new_name>
Renames the specified file or directory.

5. Generate Log File
./file_manager -l <log_file_name> <directory_path>
Generates a log file that records the actions performed on each object (file or directory) found within the given directory. If the log file already exists, it appends the new log; otherwise, it creates a new log file.

## Compilation
Compile the C program using a C compiler, such as gcc.

gcc file_operations.c -o file_operations

## Execution
Execute the compiled binary with the desired operation and required arguments.

./file_operations <operation> <arguments>

## Contributors:
Aadit Shah
Aadhya Dechamma

## Notes:
This program was developed and tested on a GNU/Linux system.
The Makefile uses the gcc compiler. It must be installed on your system.
mysql-server-core-8.0 package is required for perror used in the bash script.