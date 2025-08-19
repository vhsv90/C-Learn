#ifndef SHELL_H
#define SHELL_H

#define MAX_LINE 1024
#define MAX_ARGS 64

    void trim_newLine(char *line);
    char **parse_line(char *line);
    void free_args(char **args);
    int is_builtin(char **args);
    void run_builtin(char **args);
    void execute_command(char **args);

#endif

/*
===============================================================================
                        DEVELOPER DOCUMENTATION
===============================================================================

HEADER FILES IN C:
A header file (.h) contains function declarations, constants, and data structures
that can be shared across multiple source files. The #ifndef, #define, and #endif
directives create an "include guard" that prevents the header from being included
multiple times in the same compilation unit.

FUNCTION DECLARATIONS:

1. void trim_newLine(char *line)
   - Purpose: Removes the newline character ('\n') from the end of a string
   - Parameters: 
     * char *line: A pointer to a character array (string)
   - Returns: void (nothing)
   - Used for: Cleaning user input from fgets()

2. char **parse_line(char *line)
   - Purpose: Splits a command line into individual arguments
   - Parameters:
     * char *line: A pointer to the input string to be parsed
   - Returns: char ** (double pointer - array of string pointers)
   - Used for: Converting "ls -l file.txt" into ["ls", "-l", "file.txt", NULL]

3. void free_args(char **args)
   - Purpose: Deallocates memory allocated for command arguments
   - Parameters:
     * char **args: Double pointer to array of strings
   - Returns: void (nothing)
   - Used for: Preventing memory leaks by freeing dynamically allocated memory

4. int is_builtin(char **args)
   - Purpose: Checks if a command is a built-in shell command
   - Parameters:
     * char **args: Array of command arguments
   - Returns: int (1 if builtin, 0 if not)
   - Used for: Determining whether to handle command internally or externally

5. void run_builtin(char **args)
   - Purpose: Executes built-in shell commands (like cd, exit)
   - Parameters:
     * char **args: Array of command arguments
   - Returns: void (nothing)
   - Used for: Handling commands that don't require external programs

6. void execute_command(char **args)
   - Purpose: Executes external commands by creating new processes
   - Parameters:
     * char **args: Array of command arguments
   - Returns: void (nothing)
   - Used for: Running system programs like ls, cat, grep, etc.

POINTERS EXPLAINED:
A pointer is a variable that stores the memory address of another variable.
Think of it like a house address - it tells you where to find something.

- char *ptr: A pointer to a single character
- char **ptr: A pointer to a pointer (often used for arrays of strings)
- &variable: Gets the address of a variable
- *pointer: Dereferences a pointer (gets the value it points to)

Example:
    int x = 42;
    int *ptr = &x;  // ptr stores the address of x
    printf("%d", *ptr);  // Prints 42 (the value x points to)

CONSTANTS DEFINED:
- MAX_LINE (1024): Maximum length of a command line input
- MAX_ARGS (64): Maximum number of arguments in a single command

EXTERNAL FUNCTIONS USED:
These functions are provided by the C standard library:

From <stdio.h>:
- printf(): Outputs formatted text to console
- fgets(): Reads a line from input stream (safer than gets())
- fprintf(): Outputs formatted text to a specific stream
- perror(): Prints system error messages

From <stdlib.h>:
- malloc(): Allocates dynamic memory on the heap
- free(): Deallocates memory allocated by malloc()
- exit(): Terminates the program with a status code
- strdup(): Creates a copy of a string (allocates new memory)

From <string.h>:
- strcmp(): Compares two strings (returns 0 if equal)
- strchr(): Finds first occurrence of a character in string
- strtok(): Splits string into tokens using delimiters

From <unistd.h>:
- fork(): Creates a new process (child process)
- execvp(): Replaces current process with new program
- chdir(): Changes current working directory

From <sys/wait.h>:
- waitpid(): Waits for child process to finish and gets exit status

MEMORY MANAGEMENT:
C requires manual memory management. Every malloc() should have a corresponding 
free() to prevent memory leaks. This shell properly manages memory by:
1. Allocating memory for argument arrays in parse_line()
2. Freeing that memory in free_args() after command execution
*/