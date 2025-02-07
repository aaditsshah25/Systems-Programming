# Systems Programming Repository  
**Course:** Systems Programming  
**Instructor:** Abhijat Vichare (Visiting Faculty)  
**University:** FLAME University  

## Repository Structure  

### `flash_shell/` (Final Project: FLASH - Flame Shell)  
- Custom shell written in C with support for:  
  - Simple commands  
  - Background execution (`#` suffix)  
  - Command sequences (`,` separator)  
  - Pipes (`—` separator)  
  - Input/output redirection (`>`, `<`)  
  - Basic environment variable management  

### `file_ops/` (Single File Operations)  
- **Program:** `my_fm.c`  
- Operations on a single file or directory:  
  - Create, rename, delete  
  - Append text or binary data  
  - Read and print first 50 bytes  

### `bulk_file_ops/` (Multi File Operations)  
- **Program:** `my_bfm.c`  
- Bulk file and directory management:  
  - Create, rename, delete (including non-empty directories)  
  - Append data to files  
  - Maintain a log of actions performed  

### `process_mgmt/` (Processes Assignment)  
- **Program:** `my_cmd.c`  
- Executing binaries with process control:  
  - Run in foreground or background  
  - Capture and print process details:  
    - Command-line received  
    - Child process ID  
    - Exit code  

### `ipc_pipes/` (Pipelines - Inter-Process Communication)  
- **Program:** `my_ipc.c`  
- Implementing IPC using `pipe()` for command chaining:  
  - Handles a **data generator** (`cmd1`) and a **data consumer** (`cmd2`)  
  - Uses system calls like `open()`, `close()`, `dup2()`, `fork()`, `exec()`, and `waitpid()`  

### `file_copy/` (File Copy Utility)  
- Efficiently copies files (text and binary) with system calls  

---

Each program follows **UNIX system calls**, does **not define custom error codes**, and was developed collaboratively, emphasizing **low-level system programming, process management, and IPC mechanisms**.  
