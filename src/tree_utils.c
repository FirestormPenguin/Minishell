#include <../include/minishell.h>

t_tree *create_node(char *value)
{
  t_tree* tmp;
  
  tmp = malloc(sizeof(t_tree));
  tmp->data = value;
  tmp->left = NULL;
  tmp->right = NULL;
  return (tmp);
}

t_tree* insertLeft(t_tree* root, char *value)
{
  root->left = create_node(value);
  return (root->left);
}

t_tree* insertRight(t_tree* root, char *value)
{
  root->right = create_node(value);
  return (root->right);
}

void inorderTraversal(t_tree *root)
{
    if (root != NULL)
	{
		printf("%s \n", root->data);
        inorderTraversal(root->left);
        inorderTraversal(root->right);
    }
}