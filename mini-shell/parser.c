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