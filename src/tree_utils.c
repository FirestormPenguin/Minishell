#include <../include/minishell.h>

t_tree *create_node(t_args *args)
{
  t_tree* tmp;
  
  tmp = malloc(sizeof(t_tree));
  tmp->data = args;
  tmp->left = NULL;
  tmp->right = NULL;
  return (tmp);
}

t_tree* insertLeft(t_tree* root, t_args *args)
{
	root->left = create_node(args);
	return (root->left);
}

t_tree* insertRight(t_tree* root, t_args *args)
{
	root->right = create_node(args);
	return (root->right);
}

void inorderTraversal(t_tree *root)
{
    if (root != NULL)
	{
		printf("%s \n", root->data->str);
        inorderTraversal(root->left);
        inorderTraversal(root->right);
    }
}