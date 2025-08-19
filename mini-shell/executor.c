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
