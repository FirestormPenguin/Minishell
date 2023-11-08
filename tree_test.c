#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>

typedef struct s_node
{
   int data;

   struct s_node *left;
   struct s_node *right;
}     t_node

t_node *create_node(int value)
{
  struct t_node* tmp;
  
  tmp = malloc(sizeof(struct t_node));
  newNode->data = value;
  newNode->left = NULL;
  newNode->right = NULL;

  return (tmp);
}

t_node* insertLeft(t_node* root, int value) {
  root->left = create_node(value);
  return (root->left);
}

t_node* insertRight(t_node* root, int value) {
  root->right = create_node(value);
  return (root->right);
}

t_node *scroll_tree(int n)
{
   t_node *root;
   t_node *tmp;
   int i;

   i = -1;
   while(++i < n)
   {
      if (i == 0)
      {
         tmp = create_node(i);
         tmp->left = insertLeft(tmp);
         tmp->right = insertRight(tmp);
         root = tmp;
      }
      else
      {
         tmp = create_node(i);
      }
   }
   return (root);
}

int main(int ac, char **av) 
{
   (void) ac;
   t_node root;
   int value;

   if (ac != 2)
      return (0);
   value = 9;
   root = scroll_tree(atoi(av[1]));
   return (0); 
} 