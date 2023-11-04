#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

//gcc -o minishell minishell.c -lreadline

int main() {
    char *inputString;

    while (1) {
        inputString = readline("");
        if (strcmp(inputString, "exit") == 0)
        {
            free(inputString);
            break;
        }
        printf("Hai inserito: %s\n", inputString);
        add_history(inputString);
        free(inputString);
    }
    return 0;
}