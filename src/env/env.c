#include "../../include/minishell.h"

// Funzione per copiare le variabili d'ambiente
int copy_env(char **env, t_env4mini *all) {

    int env_size = 0;
    int i = 0;
    
    // Calcola la dimensione dell'array di stringhe delle variabili d'ambiente
    while (env[env_size] != NULL)
        env_size++;

    // Alloca dinamicamente memoria per la copia delle variabili d'ambiente in all->env
    all->env = (char **)malloc((env_size + 1) * sizeof(char *));

    if (all->env == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    // Copia ogni stringa delle variabili d'ambiente in all->env
    while (env[i] != NULL) {
        all->env[i] = strdup(env[i]);
        if (all->env[i] == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    // Imposta l'ultimo elemento di all->env a NULL per indicare la fine dell'array
    all->env[i] = NULL;

    return 1;
}

// Funzione per stampare le variabili d'ambiente copiate
void print_env_copy(t_env4mini *all) {
    int i = 0;
    while (all->env[i] != NULL) {
        printf("%s\n", all->env[i]);
        i++;
    }
}