#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

typedef struct s_tree
{
	char			*data;

	struct s_tree	*left;
	struct s_tree	*right;
}		t_tree;

/*Solito create_node*/
t_tree *create_node(char *value)
{
  t_tree* tmp;
  
  tmp = malloc(sizeof(t_tree));
  tmp->data = strdup(value);
  tmp->left = NULL;
  tmp->right = NULL;
  return (tmp);
}

/*Solito scorrimento del tree*/
void inorderTraversal(t_tree *node)
{
    if (node != NULL)
	{
		printf("%s\n", node->data);
        inorderTraversal(node->left);
        inorderTraversal(node->right);
    }
}

/*Funzione veloce per freeare il tree*/
void free_tree(t_tree *node)
{
    if (node != NULL) {
        free_tree(node->left);
        free_tree(node->right);
        free(node->data);
		free(node);
    }
}

/*Tolgo av[0] questo leggitelo perche' io non ci ho
mai pensato nella vita a farlo cosi e la mia testa
e' esplosa quando me ne sono reso conto*/
char **convert_av(char **av)
{
	char **tmp = av + 1;
	return (tmp);
}

/*Funzione ricorsiva che calcolo che se l' id e' pari inserisce
nel nodo a sinstra, se no a destra, funziona ? boh, piu o meno,
sta di fatto che piu' o meno la base logica e' una roba simile*/
t_tree *insert_node(t_tree *root, char **mtx, int *i)
{
	if (!root)
	{
		root = create_node(mtx[*i]);
		printf("Inserting node with value: %s\n", mtx[*i]);
		(*i)++;
	}
	if (!root->left && mtx[*i])
	{
		printf("Moving left, current value of i: %d\n", *i);
		root->left = insert_node(root->left, mtx, i);
	}
    if (!root->right && mtx[*i])
    {
        printf("Moving right, current value of i: %d\n", *i);
        root->right = insert_node(root->right, mtx, i);
    }
	return (root);
}

/*Scorro la matrice semplicemente e gli passo i come id da inserire nei nodi*/
t_tree *build_tree(char **mtx, int size)
{
	t_tree *root = NULL;
	int i;

	i = 0;
	root = insert_node(root, mtx, &i);

	return (root);
}

int	main(int ac, char **av)
{
	t_tree *root;
	char **mtx;

	mtx = convert_av(av);
	root = build_tree(mtx, ac - 1);
	inorderTraversal(root);
	free_tree(root);

	return (0);
}
