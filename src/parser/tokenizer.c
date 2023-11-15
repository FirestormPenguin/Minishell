#include "../../include/minishell.h"

char **tokenizer(char *input, int *token_count, char *div)
{
    char    *input_copy;
    int     count;
    char    *token;
    char    **tokens;
    int     i;

    count = 0;
    i = 0;
    input_copy = ft_strdup(input);
    token = ft_strtok(input_copy, div);
    while (token != NULL)
    {
        count++;
        token = ft_strtok(NULL, div);
    }
    tokens = (char**)malloc((count + 1) * sizeof(char*));
    token = ft_strtok(input, div);
    while (token != NULL)
    {
        tokens[i] = ft_strdup(token);
        if (tokens[i] == NULL)
            exit(1);
        i++;
        token = ft_strtok(NULL, div);
    }
    tokens[i] = NULL;
    *token_count = count;
    free(input_copy);
    return (tokens);
}
