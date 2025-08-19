#include <stdio.h>
#include "shell.h"

int main() {
    char line[MAX_LINE];

    while(1) {

        printf("krsh> ");
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