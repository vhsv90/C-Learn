#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"

int is_builtin(char **args) {
    return (strcmp(args[0], "exit") == 0 || strcmp(args[0], "cd") == 0);
}

void run_builtin(char **args) {
    if (strcmp(args[0], "exit") == 0) {
        printf("Goodbye!\n");
        exit(0);
    } else if (strcmp(args[0], "cd") == 0) {
        if (args[1]) {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        } else {
            fprintf(stderr, "cd: missing argument\n");
        }
    }
}

void execute_command(char **args) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return;
    } else if (pid == 0) {
        // Child
        execvp(args[0], args);
        perror("exec");
        exit(1);
    } else {
        // Parent
        int status;
        waitpid(pid, &status, 0);
    }
}

/*
===============================================================================
                        DEVELOPER DOCUMENTATION
===============================================================================

EXECUTOR MODULE EXPLANATION:
This module handles command execution, including both built-in commands and
external programs. It demonstrates process creation and management in Unix-like
systems.

FUNCTION IMPLEMENTATIONS:

1. int is_builtin(char **args)
   PURPOSE: Determines if a command should be handled internally
   
   PARAMETERS:
   - char **args: Array of command arguments (first element is command name)
   
   RETURN VALUE:
   - Returns 1 (true) if command is built-in, 0 (false) otherwise
   
   HOW IT WORKS:
   - Uses strcmp() to compare command name with known built-ins
   - Currently supports "exit" and "cd" commands
   - Built-ins must be handled by the shell itself, not external programs

2. void run_builtin(char **args)
   PURPOSE: Executes built-in shell commands
   
   SUPPORTED COMMANDS:
   - "exit": Terminates the shell program
   - "cd": Changes current working directory
   
   ERROR HANDLING:
   - Uses perror() to display system error messages
   - fprintf(stderr, ...) prints error to standard error stream
   
   WHY BUILT-INS EXIST:
   Some commands must be executed by the shell itself because they need to
   modify the shell's environment (like changing directory).

3. void execute_command(char **args)
   PURPOSE: Executes external programs using process creation
   
   PROCESS CREATION WORKFLOW:
   1. fork() creates identical copy of current process
   2. Child process replaces itself with new program using execvp()
   3. Parent process waits for child to complete
   
   POINTER CONCEPTS IN PROCESS MANAGEMENT:
   - pid_t: Process ID type (integer-like)
   - args[0]: Pointer to program name string
   - args: Pointer to array of argument pointers

EXTERNAL FUNCTIONS USED:

From <unistd.h>:
- fork():
  * Purpose: Creates a new process by duplicating the current process
  * Parameters: None
  * Returns: 
    - 0 in child process
    - Process ID (positive) in parent process
    - -1 on error
  * Usage: Fundamental for creating new processes in Unix

- execvp(const char *file, char *const argv[]):
  * Purpose: Replaces current process image with new program
  * Parameters:
    - file: Program name to execute
    - argv: Array of argument pointers (NULL-terminated)
  * Returns: Only returns on error (-1)
  * Behavior: Searches PATH for executable if file contains no '/'

- chdir(const char *path):
  * Purpose: Changes current working directory
  * Parameters: path - New directory path
  * Returns: 0 on success, -1 on error
  * Effect: Changes where relative paths are resolved

From <sys/wait.h>:
- waitpid(pid_t pid, int *status, int options):
  * Purpose: Waits for specific child process to change state
  * Parameters:
    - pid: Process ID to wait for
    - status: Pointer to store exit status
    - options: Behavior flags (0 for default)
  * Returns: Process ID of child that changed state
  * Usage: Prevents zombie processes and gets exit codes

From <sys/types.h>:
- pid_t:
  * Purpose: Data type for process IDs
  * Description: Usually an integer type
  * Usage: Stores process identifiers returned by fork()

From <stdlib.h>:
- exit(int status):
  * Purpose: Terminates the program immediately
  * Parameters: status - Exit code (0 for success, non-zero for error)
  * Behavior: Calls cleanup functions and closes files
  * Usage: Normal program termination

From <stdio.h>:
- printf(const char *format, ...):
  * Purpose: Prints formatted output to stdout
  * Parameters: Format string and arguments
  * Returns: Number of characters printed
  * Usage: Standard output for user messages

- fprintf(FILE *stream, const char *format, ...):
  * Purpose: Prints formatted output to specified stream
  * Parameters: Stream, format string, and arguments
  * Usage: stderr for error messages, files for logging
  * Example: fprintf(stderr, "Error: %s\n", message);

- perror(const char *s):
  * Purpose: Prints system error message to stderr
  * Parameters: s - Prefix string for error message
  * Behavior: Automatically includes errno-based error description
  * Example: If chdir() fails, perror("cd") might print "cd: No such file or directory"

From <string.h>:
- strcmp(const char *s1, const char *s2):
  * Purpose: Compares two strings lexicographically
  * Parameters: s1, s2 - Strings to compare
  * Returns: 
    - 0 if strings are equal
    - Negative if s1 < s2
    - Positive if s1 > s2
  * Usage: String comparison for command identification

PROCESS MANAGEMENT CONCEPTS:

WHAT IS A PROCESS?
A process is a running instance of a program. Each process has:
- Unique Process ID (PID)
- Memory space (code, data, heap, stack)
- Open file descriptors
- Environment variables
- Current working directory

FORK() SYSTEM CALL:
Creates an exact copy of the calling process. After fork():
- Both processes continue execution from the same point
- Child process gets PID 0 from fork()
- Parent process gets child's actual PID from fork()
- Both processes have separate memory spaces

EXEC FAMILY FUNCTIONS:
Replace the current process image with a new program:
- execvp() searches PATH and takes array of arguments
- execl() takes arguments as separate parameters
- execve() doesn't search PATH, requires full path

PROCESS STATES:
- Running: Currently executing on CPU
- Ready: Waiting for CPU time
- Blocked: Waiting for I/O or other event
- Zombie: Finished but parent hasn't collected exit status

PARENT-CHILD RELATIONSHIP:
- Parent creates child with fork()
- Parent should wait for child with waitpid()
- If parent doesn't wait, child becomes zombie
- If parent dies first, child becomes orphan (adopted by init)

ERROR HANDLING IN SYSTEM CALLS:
Most system calls return -1 on error and set errno:
- Always check return values
- Use perror() or strerror() for error messages
- Handle errors gracefully

MEMORY AND POINTERS IN PROCESS CONTEXT:
- After fork(), both processes have identical memory
- Memory modifications in one process don't affect the other
- Pointers have same values but point to different memory spaces
- execvp() completely replaces memory, so pointers become invalid

SECURITY CONSIDERATIONS:
- execvp() searches PATH, which could be security risk
- Always validate user input before passing to exec functions
- Consider using execv() with full paths for security-critical applications
*/
