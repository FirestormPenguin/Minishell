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
