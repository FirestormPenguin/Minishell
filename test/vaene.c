#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

typedef struct s_node
{
   int data;

   struct s_node *left;
   struct s_node *right;
}     t_node;

t_node *create_node(int value)
{
  t_node* tmp;
  
  tmp = malloc(sizeof(t_node));
  tmp->data = value;
  tmp->left = NULL;
  tmp->right = NULL;
  return (tmp);
}

t_node* insertLeft(t_node* root, int value)
{
  root->left = create_node(value);
  return (root->left);
}

t_node* insertRight(t_node* root, int value)
{
  root->right = create_node(value);
  return (root->right);
}

void inorderTraversal(t_node *root)
{
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d \n", root->data);
        inorderTraversal(root->right);
    }
}

void vaene()
{
   char *vaene1 = "ma porco di quel ******";
   char *vaene2 = "te mando un triangulo porque quiero tu culo";
   char *vaene_the_final;
   int rng;

   srand(time(NULL));
   rng = rand() % 100 + 1;
   if (rng % 2 == 0)
      vaene_the_final = vaene1;
   else
      vaene_the_final = vaene2;
   printf("\nVaene:\n%s\n", vaene_the_final);
}

int main() 
{
   t_node *root;

   root = create_node(1);
   insertLeft(root, 2);
   insertRight(root, 3);
   insertLeft(root->left, 4);
   insertRight(root->left, 5);
   inorderTraversal(root);
   printf("\n");
   free(root->left);
   free(root->right);
   free(root);

   vaene();
   return (0); 
}
