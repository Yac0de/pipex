# Pipex - Understanding UNIX Pipes

## Table of Contents

1. Project Overview
2. Project Structure
3. How to Use This Project
4. Key UNIX Concepts Explained
   - Pipes
   - Fork
   - Execve
   - File Descriptors & Redirections
   - Dup vs Dup2
   - Wait vs Waitpid
   - Additional System Calls Used
5. Error Handling & Memory Management
6. Bonus Features
7. Example Usage

---

## 1. Project Overview

Pipex is a project that recreates a simple shell pipeline in C using UNIX system calls. The goal is to understand how **pipes**, **processes**, and **file redirections** work.

**Mandatory goal:**
Execute two commands with a pipe:

```sh
./pipex file1 cmd1 cmd2 file2
```

This should behave like:

```sh
< file1 cmd1 | cmd2 > file2
```

**Bonus:**

- Handle multiple commands (`cmd1 | cmd2 | ... | cmdn`)
- Implement `here_doc` (`<< LIMITER`)

---

## 2. Project Structure

```
.
├── Makefile
├── inc
│   └── pipex.h
├── libft
├── src
│   ├── check_input.c
│   ├── children.c
│   ├── error.c
│   ├── free.c
│   ├── get_path.c
│   └── pipex.c
└── src_bonus
    ├── check_input_bonus.c
    ├── children_bonus.c
    ├── error_bonus.c
    ├── free_bonus.c
    ├── get_path_bonus.c
    ├── here_doc_bonus.c
    ├── init_pipes_bonus.c
    └── pipex_bonus.c
```

---

## 3. How to Use This Project

### **Compiling**

```sh
make
```

### **Executing the program**

```sh
./pipex file1 "cmd1" "cmd2" file2
```

Example:

```sh
./pipex infile "ls -l" "wc -l" outfile
```

This should produce the same output as:

```sh
< infile ls -l | wc -l > outfile
```

For bonus:

```sh
./pipex file1 "cmd1" "cmd2" "cmd3" file2
./pipex here_doc LIMITER cmd1 cmd2 file2
```

---

## 4. Key UNIX Concepts Explained

### **Pipes**

A **pipe** is a unidirectional communication channel used for **inter-process communication (IPC)**. It allows one process to send data to another. Pipes are created using:

```c
int pipe(fd);
```

where `fd[0]` is the read end and `fd[1]` is the write end.

### **Fork**

`fork()` creates a **child process**, which is an exact copy of the parent. Each process gets its own execution flow.

```c
pid_t pid = fork();
```

- If `pid == 0`, we are in the **child** process.
- If `pid > 0`, we are in the **parent** process.

### **Execve**

`execve()` replaces the current process with a new program. It is used to execute commands.

```c
execve(path, args, envp);
```

- `path` is the absolute path to the command.
- `args` is an array of arguments (`args[0]` is the command name).
- `envp` is the environment variables.

### **File Descriptors & Redirections**

- **STDIN (0)** → Standard input
- **STDOUT (1)** → Standard output
- **STDERR (2)** → Standard error

To redirect input/output:

```c
dup2(fd, STDIN_FILENO); // Redirects stdin to fd
dup2(fd, STDOUT_FILENO); // Redirects stdout to fd
```

### **Dup vs Dup2**

Both `dup` and `dup2` duplicate file descriptors, but they have different behaviors:

- `dup(oldfd)`: Creates a new file descriptor that refers to the same resource as `oldfd`. The new file descriptor is the lowest available number.
- `dup2(oldfd, newfd)`: Duplicates `oldfd` into `newfd`. If `newfd` is already open, it is first closed before being reassigned.

```c
int new_fd = dup(fd);
dup2(fd, STDOUT_FILENO);
```

This ensures that output is redirected properly.

### **Wait vs Waitpid**

Both `wait` and `waitpid` are used to wait for child processes to finish execution, but they have key differences:

- `wait(NULL)`: Waits for **any child process** to terminate.
- `waitpid(pid, &status, options)`: Waits for a **specific child process** identified by `pid`.

```c
int status;
waitpid(child_pid, &status, 0);
```

This allows more control, such as waiting for a **specific** child process or using flags for non-blocking behavior.

### **Additional System Calls Used**

- `perror()`: Displays an error message corresponding to the last system error.
- `strerror()`: Returns a string describing an error code.
- `access()`: Checks file permissions before opening.
- `unlink()`: Removes a file from the filesystem.

---

## 5. Error Handling & Memory Management

- **Error handling:** The program handles invalid inputs, missing files, and permission errors.
- **Memory management:** All dynamically allocated memory is freed properly to prevent leaks.
- **File descriptors:** Are always closed when no longer needed.

---

## 6. Bonus Features

✅ **Handling multiple commands**

```sh
./pipex infile "cmd1" "cmd2" "cmd3" "cmd4" outfile
```

This behaves like:

```sh
< infile cmd1 | cmd2 | cmd3 | cmd4 > outfile
```

✅ **`here_doc`**\*\* support\*\*

```sh
./pipex here_doc LIMITER cmd1 cmd2 file2
```

This behaves like:

```sh
cmd1 << LIMITER | cmd2 >> file2
```

---

## 7. Example Usage

### **Basic Execution**

```sh
./pipex infile "cat" "grep foo" outfile
```

Equivalent to:

```sh
< infile cat | grep foo > outfile
```

### **Bonus - Multiple Commands**

```sh
./pipex infile "cat" "grep foo" "wc -l" outfile
```

Equivalent to:

```sh
< infile cat | grep foo | wc -l > outfile
```

### **Bonus - Here Document**

```sh
./pipex here_doc EOF cat "grep foo" output.txt
```

You can now type input until `EOF`, and it will be processed by `cat | grep foo`.

---
