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