#include <stdio.h>
#include <stdlib.h>

// Struttura del nodo dell'albero
typedef struct t_tree {
    char *value;
    struct t_tree *left;
    struct t_tree *right;
} t_tree;

// Struttura del nodo nella coda
typedef struct QueueNode {
    t_tree *node;           // Puntatore al nodo dell'albero
    struct QueueNode *next;  // Puntatore al prossimo nodo nella coda
} QueueNode;

// Struttura della coda
typedef struct {
    QueueNode *front;  // Puntatore al nodo in testa alla coda (primi elementi)
    QueueNode *rear;   // Puntatore al nodo in fondo alla coda (ultimi elementi)
} Queue;

// Funzione per creare un nuovo nodo dell'albero
t_tree *create_node(char *value) {
    t_tree *new_node = malloc(sizeof(t_tree));
    if (!new_node) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

// Funzione per creare una nuova coda
Queue *create_queue() {
    Queue *queue = malloc(sizeof(Queue));
    if (!queue) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    queue->front = NULL;  // Inizializza il puntatore alla testa a NULL (coda vuota)
    queue->rear = NULL;   // Inizializza il puntatore alla coda a NULL (coda vuota)

    return queue;
}

// Funzione per inserire un nodo alla fine della coda
void enqueue(Queue *queue, t_tree *node) {
    QueueNode *new_node = malloc(sizeof(QueueNode));
    if (!new_node) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    new_node->node = node;  // Assegna il nodo all'elemento della coda
    new_node->next = NULL;  // Il nuovo nodo sarà l'ultimo, quindi il suo next è NULL

    // Se la coda è vuota, il nuovo nodo è sia in testa che in fondo
    if (queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        // Altrimenti, aggiungi il nuovo nodo alla fine della coda
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

// Funzione per rimuovere e restituire il nodo in testa alla coda
t_tree *dequeue(Queue *queue) {
    // Se la coda è vuota, restituisci NULL
    if (queue->front == NULL) {
        return NULL;
    }

    QueueNode *temp = queue->front;  // Salva il puntatore al nodo in testa
    t_tree *node = temp->node;       // Salva il nodo da restituire

    // Avanza il puntatore alla testa alla prossima posizione
    queue->front = queue->front->next;
    free(temp);  // Libera il nodo rimosso dalla memoria

    // Se la coda è ora vuota, aggiorna anche il puntatore alla fine
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return node;
}

// Funzione per inserire i nodi nell'albero seguendo un attraversamento per livelli
void level_order_insert(t_tree **root, char **mtx, int *i) {
    Queue *queue = create_queue();

    // Se l'albero è vuoto, crea il nodo radice
    if (*root == NULL) {
        *root = create_node(mtx[*i]);
        printf("Inserting root node with value: %s\n", mtx[*i]);
        (*i)++;
        enqueue(queue, *root);
    }

    // Finché ci sono nodi nella coda da esplorare
    while (1) {
        // Prendi il nodo corrente dalla coda
        t_tree *current = dequeue(queue);

        // Se tutti i nodi sono stati esplorati, esci
        if (current == NULL) {
            break;
        }

    	// Se il sottoalbero sinistro è vuoto e c'è un valore nella matrice
        if (current->left == NULL && mtx[*i] != NULL) {
            // Crea un nuovo nodo e inseriscilo come figlio sinistro
            current->left = create_node(mtx[*i]);
            printf("Inserting left child with value: %s\n", mtx[*i]);
            (*i)++;
            // Aggiungi il nuovo nodo alla coda per l'esplorazione successiva
            enqueue(queue, current->left);
        }

        // Se il sottoalbero destro è vuoto e c'è un valore nella matrice
        if (current->right == NULL && mtx[*i] != NULL) {
            // Crea un nuovo nodo e inseriscilo come figlio destro
            current->right = create_node(mtx[*i]);
            printf("Inserting right child with value: %s\n", mtx[*i]);
            (*i)++;
            // Aggiungi il nuovo nodo alla coda per l'esplorazione successiva
            enqueue(queue, current->right);
        }
    }

    // Libera la memoria occupata dalla coda
    free(queue);
}

int main() {
    // Esempio di matrice con valori
    char *matrix[] = {"3", "2", "GJS_DEBUG_TOPICS=JS ERROR;JS LOG", "USER=spiacent", NULL};

    // Inizializza l'albero e l'indice
    t_tree *root = NULL;
    int i = 0;

    // Chiama la funzione per l'inserimento per livelli
    level_order_insert(&root, matrix, &i);

    // Ora l'albero dovrebbe essere riempito correttamente

    return 0;
}
