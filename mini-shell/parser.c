#include <stdlib.h>
#include <string.h>
#include "shell.h"

void trim_newLine(char *line) {
    char *p = strchr(line, '\n');
    if(p) *p = '\0';
}

char **parse_line(char *line) {
    char **args = malloc(MAX_ARGS * sizeof(char *));
    if(!args) return NULL;

    int i = 0;
    char *token = strtok(line, " ");

    while (token != NULL && i < MAX_ARGS -1)
    {
        args[i++] = strdup(token);
        token = strtok(NULL, " ");
    }

    args[i] = NULL;
    return args;    
}

void free_args(char **args) {
    int i = 0;

    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

/*
===============================================================================
                        DEVELOPER DOCUMENTATION
===============================================================================

PARSER MODULE EXPLANATION:
This module handles parsing and memory management for command line input.
It's responsible for converting user input into a format the shell can execute.

FUNCTION IMPLEMENTATIONS:

1. void trim_newLine(char *line)
   PURPOSE: Removes trailing newline character from user input
   
   POINTER CONCEPTS:
   - char *line: Pointer to first character of string
   - char *p: Pointer to location of newline character
   
   HOW IT WORKS:
   - strchr() searches for '\n' character and returns pointer to it
   - if(p) checks if newline was found (pointer is not NULL)
   - *p = '\0' replaces newline with null terminator (end of string)
   
   POINTER EXPLANATION:
   When you declare "char *p", you're creating a variable that can store
   the memory address of a character. The * operator is used to:
   - Declare a pointer: char *p;
   - Dereference (access value): *p = '\0';

2. char **parse_line(char *line)
   PURPOSE: Splits command line into array of individual arguments
   
   DOUBLE POINTER CONCEPT:
   - char **args: Pointer to pointer (array of string pointers)
   - Think of it as: args[0] -> "ls", args[1] -> "-l", args[2] -> NULL
   
   MEMORY ALLOCATION:
   - malloc() allocates memory on the heap (persistent until freed)
   - sizeof(char *) calculates size of one pointer
   - MAX_ARGS * sizeof(char *) allocates space for array of pointers
   
   TOKENIZATION PROCESS:
   - strtok(line, " ") splits string at space characters
   - First call uses original string
   - Subsequent calls use NULL to continue from last position
   - strdup() creates copy of each token (allocates new memory)
   
   RETURN VALUE:
   Returns pointer to array of string pointers, or NULL if allocation fails

3. void free_args(char **args)
   PURPOSE: Deallocates all memory allocated by parse_line()
   
   MEMORY CLEANUP PROCESS:
   - Loop through each string pointer in the array
   - free(args[i]) deallocates each individual string
   - free(args) deallocates the array of pointers itself
   
   WHY THIS IS NECESSARY:
   C doesn't have garbage collection. Every malloc() and strdup() must
   have a corresponding free() to prevent memory leaks.

EXTERNAL FUNCTIONS USED:

From <string.h>:
- strchr(const char *str, int c):
  * Purpose: Searches for first occurrence of character in string
  * Parameters: 
    - str: String to search in
    - c: Character to find
  * Returns: Pointer to character if found, NULL if not found
  * Example: strchr("hello", 'l') returns pointer to first 'l'

- strtok(char *str, const char *delim):
  * Purpose: Splits string into tokens using specified delimiters
  * Parameters:
    - str: String to tokenize (NULL for subsequent calls)
    - delim: String containing delimiter characters
  * Returns: Pointer to next token, NULL when no more tokens
  * Warning: Modifies original string by inserting null terminators
  * Example: strtok("a,b,c", ",") returns "a", then "b", then "c"

- strdup(const char *s):
  * Purpose: Creates duplicate copy of string in new memory
  * Parameters: s - String to duplicate
  * Returns: Pointer to new string copy, NULL if allocation fails
  * Memory: Allocates new memory that must be freed later
  * Equivalent to: malloc + strcpy

From <stdlib.h>:
- malloc(size_t size):
  * Purpose: Allocates specified number of bytes on heap
  * Parameters: size - Number of bytes to allocate
  * Returns: Pointer to allocated memory, NULL if allocation fails
  * Usage: Must be paired with free() to prevent memory leaks
  * Example: malloc(10) allocates 10 bytes

- free(void *ptr):
  * Purpose: Deallocates memory previously allocated by malloc/strdup
  * Parameters: ptr - Pointer to memory to free
  * Returns: Nothing (void)
  * Warning: Don't use pointer after freeing (undefined behavior)
  * Example: free(ptr); ptr = NULL; // Good practice

POINTER DEEP DIVE:
Pointers are fundamental to C programming. Here's a comprehensive explanation:

WHAT IS A POINTER?
A pointer is a variable that stores the memory address of another variable.

POINTER SYNTAX:
- int *ptr;        // Declares pointer to integer
- ptr = &variable; // Assigns address of variable to ptr
- *ptr = 5;        // Assigns value 5 to location ptr points to
- value = *ptr;    // Reads value from location ptr points to

POINTER ARITHMETIC:
- ptr++            // Move to next memory location
- ptr + 1          // Address of next element
- ptr - ptr2       // Distance between pointers

ARRAY AND POINTER RELATIONSHIP:
- int arr[5];      // Array of 5 integers
- int *ptr = arr;  // ptr points to first element
- arr[i] == *(ptr + i)  // These are equivalent

DOUBLE POINTERS (POINTER TO POINTER):
char **args is a pointer to a pointer. It's commonly used for:
- Arrays of strings (each string is char*, array of them is char**)
- Dynamic 2D arrays
- Modifying pointer values in functions

MEMORY LAYOUT EXAMPLE:
char **args after parse_line("ls -l file.txt"):

Memory Address | Content
----------------|----------
0x1000         | 0x2000    <- args[0] points to "ls"
0x1008         | 0x2010    <- args[1] points to "-l"  
0x1016         | 0x2020    <- args[2] points to "file.txt"
0x1024         | NULL      <- args[3] is NULL (end marker)

0x2000         | "ls\0"    <- First string
0x2010         | "-l\0"    <- Second string
0x2020         | "file.txt\0" <- Third string

COMMON POINTER MISTAKES:
1. Using uninitialized pointers
2. Dereferencing NULL pointers
3. Memory leaks (forgetting to free())
4. Double free (calling free() twice)
5. Using freed memory (dangling pointers)

GOOD PRACTICES:
1. Always check if malloc() returns NULL
2. Set pointers to NULL after freeing
3. Free memory in reverse order of allocation
4. Use tools like valgrind to detect memory issues
*/