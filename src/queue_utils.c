#include <../include/minishell.h>

Queue *create_queue()
{
    Queue *queue;
	
	queue = malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}

void destroy_queue(Queue *queue)
{
    while (queue->front != NULL)
	{
        QueueNode *temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
    }

    free(queue);
}

void enqueue(Queue *queue, t_tree *node)
{
	QueueNode *new_node;

	new_node = malloc(sizeof(QueueNode));

	new_node->node = node;
	new_node->next = NULL;

    if (queue->rear == NULL)
	{
        queue->front = new_node;
        queue->rear = new_node;
    }
	else
	{
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

t_tree *dequeue(Queue *queue)
{
	QueueNode *temp;
	t_tree *node;

    if (queue->front == NULL)
        return NULL; // Coda vuota

    temp = queue->front;
    node = temp->node;
	
    queue->front = queue->front->next;
    free(temp);
    if (queue->front == NULL)
        queue->rear = NULL; // L'ultimo nodo è stato rimosso
    return (node);
}
