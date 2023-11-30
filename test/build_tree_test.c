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

t_tree *create_node(char *value)
{
  t_tree* tmp;
  
  tmp = malloc(sizeof(t_tree));
  tmp->data = value;
  tmp->left = NULL;
  tmp->right = NULL;
  return (tmp);
}

t_tree* insertLeft(t_tree* node, char *value)
{
  node->left = create_node(value);
  return (node->left);
}

t_tree* insertRight(t_tree* node, char *value)
{
  node->right = create_node(value);
  return (node->right);
}

void inorderTraversal(t_tree *node)
{
    if (node != NULL)
	{
		printf("%s\n", node->data);
        inorderTraversal(node->left);
        inorderTraversal(node->right);
    }
}

void free_tree(t_tree *node)
{
    if (node != NULL) {
        free_tree(node->left);
        free_tree(node->right);
		free(node);
    }
}

char **convert_av(char **av)
{
	char **tmp = av + 1;
	return (tmp);
}

t_tree *insert_node(t_tree *root, char *value, int *inserted)
{
	if (root == NULL) {
        *inserted = 1;
        return create_node(value);
    }

    int compare_result = strcmp(value, root->data);

    if (compare_result < 0) {
        root->left = insert_node(root->left, value);
    } else if (compare_result > 0) {
        root->right = insert_node(root->right, value);
    }

    return root;
}

t_tree *build_tree(char **mtx, int size)
{
	t_tree *root = NULL;
	int i;

	i = 0;
	while (i < size)
	{
		root = insert_node(root, mtx[i]);
		i++;
	}
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
