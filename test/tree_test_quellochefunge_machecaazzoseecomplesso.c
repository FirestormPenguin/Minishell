#include <stdio.h>
#include <stdlib.h>

typedef struct t_tree
{
    char *value;
    struct t_tree *left;
    struct t_tree *right;
} t_tree;

typedef struct QueueNode
{
    t_tree *node;
    struct QueueNode *next;
} QueueNode;

typedef struct
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

t_tree *create_node(char *value)
{
    t_tree *new_node;

	new_node = malloc(sizeof(t_tree));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    return (new_node);
}

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

void level_order_insert(t_tree **root, char **mtx, int *i)
{
    Queue *queue;
	t_tree *current;

	queue = create_queue();
    if (*root == NULL)
	{
        *root = create_node(mtx[*i]);
        (*i)++;
        enqueue(queue, *root);
    }

    while (1)
	{
        current = dequeue(queue);

        if (current == NULL)
            break; // Tutti i nodi esplorati
        if (current->left == NULL && mtx[*i] != NULL)
		{
            current->left = create_node(mtx[*i]);
            (*i)++;
            enqueue(queue, current->left);
        }
        if (current->right == NULL && mtx[*i] != NULL)
		{
            current->right = create_node(mtx[*i]);
            (*i)++;
            enqueue(queue, current->right);
        }
    }
	destroy_queue(queue);
}

char **convert_av(char **av)
{
	char **tmp = av + 1;
	return (tmp);
}

void inorderTraversal(t_tree *node)
{
    if (node != NULL)
	{
		printf("%s\n", node->value);
        inorderTraversal(node->left);
        inorderTraversal(node->right);
    }
}

t_tree *build_tree(char **mtx, int size)
{
	t_tree *root = NULL;
	int i;

	i = 0;
	level_order_insert(&root, mtx, &i);

	return (root);
}

int	main(int ac, char **av)
{
	t_tree *root;
	char *mtx[] = {"|", "ls", "pwd", "-la", NULL, "file", NULL};

	//mtx = convert_av(av);
	root = build_tree(mtx, ac - 1);
	inorderTraversal(root);

	return (0);
}
