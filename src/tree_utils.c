#include <../include/minishell.h>

t_tree *create_node(char *str)
{
  t_tree* tmp;
  
  tmp = malloc(sizeof(t_tree));
  tmp->data = str;
  tmp->left = NULL;
  tmp->right = NULL;
  return (tmp);
}

t_tree* insertLeft(t_tree* root, t_args *args)
{
	root->left = create_node(args->str);
	return (root->left);
}

t_tree* insertRight(t_tree* root, t_args *args)
{
	root->right = create_node(args->str);
	return (root->right);
}

// void inorderTraversal(t_tree *root)
// {
//     if (root)
// 	{
// 		printf("Root: %s \n", root->data);
//         if (root->left)
//             printf("Left Child: %s \n", root->left->data);
//         if (root->right)
//             printf("Right Child: %s \n", root->right->data);
//         inorderTraversal(root->left);
//         inorderTraversal(root->right);
//     }
// }

void inorderTraversal(t_tree *root)
{
    if (root)
	{
		printf("\t%s \n", root->data);
        if (root->left)
            inorderTraversal(root->left);
        if (root->right)
            inorderTraversal(root->right);
    }
}
