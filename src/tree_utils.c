#include <../include/minishell.h>

t_tree *create_node(char *str, int type, t_tree *prevNode, t_tree *rootNode)
{
  t_tree* tmp;
  
  tmp = malloc(sizeof(t_tree));
  tmp->data = str;
  tmp->type = type;
  tmp->parent = rootNode;
  tmp->left = NULL;
  tmp->right = NULL;
  tmp->prev = prevNode;
  return (tmp);
}

void inorderTraversal(t_tree *root)
{
    if (root)
	{
		printf("\n\tstr: %s\n", root->data);
		if (root->prev)
			printf("\tprev: %s\n", root->prev->data);
        if (root->left)
            inorderTraversal(root->left);
        if (root->right)
            inorderTraversal(root->right);
    }
}
