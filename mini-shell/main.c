#include <stdio.h>
#include "shell.h"

int main() {
    char line[MAX_LINE];

    while(1) {

        printf("pupa-cli> ");
        if(!fgets(line, MAX_LINE, stdin)) {
            break;
        }

        // remove trailing newline
        trim_newLine(line);

        // ignore empty input
        if(line[0] == '\0') continue;

        // parse and execute
        char **args = parse_line(line);
        if (args == NULL) continue;

        if(is_builtin(args)) {
            run_builtin(args);
        } else {
            execute_command(args);
        }

        free_args(args);
    }

    return 0;
}

/*
===============================================================================
                        DEVELOPER DOCUMENTATION
===============================================================================

MAIN FUNCTION EXPLANATION:
The main() function is the entry point of every C program. When you run the 
program, execution starts here. This function implements the main shell loop
that reads user input, parses it, and executes commands.

PROGRAM FLOW:
1. Declare a character array to store user input
2. Enter infinite loop to continuously accept commands
3. Display shell prompt "krsh> "
4. Read user input using fgets()
5. Clean the input by removing newline character
6. Skip empty input lines
7. Parse the command line into arguments
8. Check if it's a built-in command or external command
9. Execute the appropriate command
10. Free allocated memory
11. Repeat until user exits

VARIABLES EXPLAINED:
- char line[MAX_LINE]: A character array (string) to store user input
  * Arrays in C are collections of elements of the same type
  * line[0] accesses the first character, line[1] the second, etc.
  * MAX_LINE (1024) defines the maximum input length

- char **args: A double pointer returned by parse_line()
  * This represents an array of strings (command arguments)
  * Each element points to a different argument string

CONTROL STRUCTURES:

1. while(1) - Infinite Loop:
   * Continues until explicitly broken with exit command
   * The condition (1) is always true

2. if(!fgets(line, MAX_LINE, stdin)):
   * fgets() returns NULL on error or end-of-file
   * The ! operator negates the result (converts NULL to true)
   * This breaks the loop if input fails (Ctrl+D pressed)

3. if(line[0] == '\0'):
   * Checks if the first character is null terminator
   * Empty strings have '\0' as their first character
   * continue skips to next loop iteration

EXTERNAL FUNCTIONS USED:

From <stdio.h>:
- printf(format, ...):
  * Purpose: Prints formatted output to console
  * Parameters: Format string and optional arguments
  * Returns: Number of characters printed
  * Example: printf("Hello %s\n", "World");

- fgets(buffer, size, stream):
  * Purpose: Reads a line from input stream (safer than gets())
  * Parameters: 
    - buffer: Character array to store input
    - size: Maximum characters to read
    - stream: Input source (stdin for keyboard)
  * Returns: Pointer to buffer on success, NULL on error/EOF
  * Advantage: Prevents buffer overflow by limiting input size

From "shell.h" (our custom functions):
- trim_newLine(line):
  * Purpose: Removes '\n' character added by fgets()
  * Why needed: fgets() includes newline in the string

- parse_line(line):
  * Purpose: Splits command string into array of arguments
  * Returns: Array of string pointers (char **)

- is_builtin(args):
  * Purpose: Checks if command is handled internally
  * Returns: 1 (true) for built-ins like "exit" and "cd"

- run_builtin(args):
  * Purpose: Executes built-in commands

- execute_command(args):
  * Purpose: Runs external programs using system calls

- free_args(args):
  * Purpose: Deallocates memory to prevent memory leaks

MEMORY MANAGEMENT CONCEPTS:
C requires manual memory management. When parse_line() allocates memory
using malloc(), we must call free_args() to return that memory to the system.
Failure to do this causes memory leaks.

ARRAY vs POINTER CONCEPTS:
- char line[MAX_LINE]: Stack-allocated array (automatic memory)
- char **args: Pointer to dynamically allocated memory (heap memory)

Stack memory is automatically cleaned up when the function ends.
Heap memory must be manually freed with free().

RETURN VALUE:
The main() function returns 0 to indicate successful program execution.
Non-zero return values typically indicate errors.
*/