/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 23:53:44 by mivendit          #+#    #+#             */
/*   Updated: 2024/02/08 23:53:44 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/libft.h"

void    swap(char** a, char** b)
{
    char* t = *a;
    *a = *b;
    *b = t;
}

int partition (char* arr[], int low, int high)
{
    char *pivot;
    int i;
    int j;

    pivot = arr[high];
    i = low - 1;
    j = low;
    while (j <= high - 1) 
    {
        if (ft_strcmp(arr[j], pivot) < 0) 
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
        j++;
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void    ft_qsort(char **arr, int low, int high)
{
    int pi;

    if (low < high) 
    {
        pi = partition(arr, low, high);

        ft_qsort(arr, low, pi - 1);
        ft_qsort(arr, pi + 1, high);
    }
}

/* Dopo la chiamata iniziale, l'array viene partizionato attorno al pivot "a" (l'ultimo elemento)
Tutti gli elementi minori di "a" vengono spostati a sinistra, e tutti gli elementi maggiori a destra
Ma dato che "a" è l'elemento più piccolo, finisce per essere il primo elemento dell'array
Array dopo la partizione: {"a", "e", "d", "c", "b", "f"}

Ora ft_qsort viene chiamato ricorsivamente per i sottosegmenti a sinistra e a destra del pivot

Sottosegmento sinistro: {"e", "d", "c", "b"}
Il pivot per questo sottosegmento è "b"
Dopo la partizione, l'array diventa: {"a", "b", "d", "c", "e", "f"}

Sottosegmento sinistro del sottosegmento sinistro: {"d", "c"}
Il pivot per questo sottosegmento è "c"
Dopo la partizione, l'array diventa: {"a", "b", "c", "d", "e", "f"}

A questo punto, tutti i sottosegmenti sinistri sono ordinati
Non ci sono sottosegmenti destri in questo esempio, quindi l'array è completamente ordinato */