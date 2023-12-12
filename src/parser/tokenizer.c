/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirko <mirko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2023/12/12 17:33:28 by mirko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// char **tokenizer(char *input, int *token_count) {
//     char    *input_copy; // Copia dell'input
//     int     count; // Contatore per i token
//     char    **tokens; // Array di token
//     int     i; // Contatore per l'array di token
//     bool    in_quote; // Flag per tenere traccia se si è all'interno di un apice
//     char    quote_type; // Tipo di apice (singolo o doppio)

//     count = 0; // Inizializza il contatore dei token
//     i = 0; // Inizializza il contatore per l'array di token
//     in_quote = false; // Inizializza il flag degli apici a falso (non dentro un apice)
//     input_copy = ft_strdup(input); // Copia l'input per lavorarci sopra
//     tokens = malloc((strlen(input) + 1) * sizeof(char *)); // Alloca memoria per l'array di token
//     if (!tokens) // Gestione errore: verifica se l'allocazione di memoria è andata male
//         return NULL;

//     // Ciclo principale che scorre l'input per estrarre i token
//     while (*input_copy != '\0') {
//         // Salta gli spazi e le tabulazioni
//         while (*input_copy && (*input_copy == ' ' || *input_copy == '\t'))
//             input_copy++;
        
//         if (!*input_copy) // Se siamo alla fine dell'input, esci dal ciclo
//             break;

//         if (is_quote(*input_copy)) { // Se il carattere è un apice singolo o doppio
//             in_quote = true; // Imposta il flag degli apici a true
//             quote_type = *input_copy; // Salva il tipo di apice
//             input_copy++;
//             tokens[i++] = input_copy; // Salta il token all'interno degli apici

//             // Ciclo per trovare l'apice di chiusura
//             while (*input_copy && (*input_copy != quote_type || (*(input_copy - 1) == '\\' && *input_copy == quote_type))) {
//                 input_copy++;
//             }

//             if (*input_copy == quote_type) { // Se trovi l'apice di chiusura
//                 in_quote = false; // Imposta il flag degli apici a false (usciamo dall'apice)
//                 *input_copy++ = '\0'; // Sostituisce l'apice di chiusura con '\0' per terminare il token
//             } else {
//                 printf("Errore: incorrect quotes\n");
//                 free(tokens); // Libera la memoria allocata per l'array di token
//                 *token_count = 0; // Imposta il conteggio dei token a zero
//                 return NULL; // Restituisci NULL per segnalare un errore
//             }
//         } else if (*input_copy == '|' && !in_quote) { // Se il carattere è un pipe e non siamo dentro un apice
//             tokens[i++] = input_copy; // Assegna il token corrente all'array di token
//             *input_copy++ = '\0'; // Sostituisce il separatore con '\0' per terminare il token
//             count++; // Incrementa il contatore dei token
//         } else {
//             tokens[i++] = input_copy; // Assegna il token corrente all'array di token

//             // Ciclo per estrarre il token corrente
//             while (*input_copy && !is_quote(*input_copy) && (*input_copy != ' ' && *input_copy != '\t' && *input_copy != '|')) {
//                 input_copy++;
//             }

//             if (*input_copy) // Se non siamo alla fine dell'input
//                 *input_copy++ = '\0'; // Sostituisce il separatore con '\0' per terminare il token

//             count++; // Incrementa il contatore dei token
//         }
//     }

//     *token_count = count; // Imposta il conteggio dei token corretto
//     tokens[count] = NULL; // Imposta l'ultimo elemento dell'array di token a NULL per segnalare la fine
//     return tokens; // Restituisce l'array di token
// }

char **tokenizer(char *input, int *token_count)
{
    char *input_copy;
    int count;
    char tmp_token[50];
    char **tokens;
    int i1;
    int i2;
    int i3;
    bool in_quote;
    
    printf("Enter tokenizer\n");
    input_copy = ft_strdup(input);
	in_quote = 0; 
    count = 0;
    tokens = malloc((strlen(input) + 1) * sizeof(char *));
    i1 = 0;
    i3 = 0;
    while (input_copy[i1])
    {
        
        while (input_copy[i1] == ' ' || input_copy[i1] == '\t')
        {
            i1++;
        }
        i2 = 0;
        while (input_copy[i1])
        {
            if (input_copy[i1] == ' ' || input_copy[i1] == '\t')
            {
                i1++;
                break;
            }
            else if (input_copy[i1] == '|')
            {
                tmp_token[i2] = '|';
                i2++;
                i1++;
                break;
            }
            else if (input_copy[i1] == '>' && input_copy[i1 + 1] != '>')
            {
                tmp_token[i2] = '>';
                i2++;
                i1++;
                break;
            }
            else if (input_copy[i1] == '<' && !input_copy[i1 + 1] == '<')
            {
                tmp_token[i2] = '<';
                i2++;
                i1++;
                break;
            }
            else if (input_copy[i1] == '>' && input_copy[i1 + 1] == '>')
            {
                tmp_token[i2] = '>';
                tmp_token[i2 + 1] = '>';
                i2++;
                i2++;
                i1++;
                i1++;
                break;
            }
            else if (input_copy[i1] == '<' && input_copy[i1 + 1] == '<')
            {
                tmp_token[i2] = '<';
                tmp_token[i2 + 1] = '<';
                i2++;
                i2++;
                i1++;
                i1++;
                break;
            }
            else if (input_copy[i1] == '"' || input_copy[i1] == '\'')
            {   
				in_quote = 1;
				i1++;
                while (input_copy[i1])
                {
					if (input_copy[i1] == '"' || input_copy[i1] == '\'')
					{
						in_quote = 0;
						i1++;
						break;
					}
                    tmp_token[i2] = input_copy[i1];
                    i2++;
					i1++;
                }
				if (in_quote == 0)
					break;
            }
            else
            {
                tmp_token[i2] = input_copy[i1];
				i2++;
                i1++;
                if (input_copy[i1] == ' ' || input_copy[i1] == '\t'
                    || input_copy[i1] == '|' || input_copy[i1] == '>'
                    || input_copy[i1] == '<')
                    break;
            }
        }
        tmp_token[i2] = '\0';
        tokens[i3] = ft_strdup(tmp_token);
        i3++;
        count++;
    }
    *token_count = count;
    tokens[count] = NULL;
	if (in_quote == 1)
	{
		printf("Error: unclosed quote\n");
		return (NULL);
	}
    return (tokens);
}
