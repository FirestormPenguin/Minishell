void	tokenize_string_tree(char *str)
{
	t_args	*args;
	t_tree	*root;
	char	**mtx;
	int		arg_count;
	int		pipe_count;
	int		i;

	mtx = tokenizer(str, &arg_count);
	i = 0;
	if (mtx == NULL)
		return ;
	args = fill_struct(mtx, arg_count);
	check_type(args, arg_count, &pipe_count);
	root = build_tree(args, pipe_count, arg_count);
	inorderTraversal(root);
}

void check_type(t_args *args, int count, int *pipe_count)
{
	int i;
	int tmp_pipe_count;

	i = -1;
	tmp_pipe_count = 0;
	while (++i < count)
	{
		if (ft_strcmp(args[i].str, "|") == 0)
		{
			args[i].type = TOKEN_PIPE;
			tmp_pipe_count++;
		}
		else if (ft_strcmp(args[i].str, "<") == 0 || ft_strcmp(args[i].str, ">") == 0)
			args[i].type = TOKEN_REDIR;
		else if (ft_strcmp(args[i].str, ">>") == 0)
			args[i].type = TOKEN_DOUBLE_OUT;
		else if (ft_strcmp(args[i].str, "<<") == 0)
			args[i].type = TOKEN_HERE_DOC;
		else
			args[i].type = TOKEN_WORD;
	}
	*pipe_count = tmp_pipe_count;
}

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

t_list	*init_list(char **mtx)
{
	int		i;
	int		j;
	t_list	*list_h;
	t_list	*list;
	int		next_type;

	i = 0;
	list_h = NULL;
	list = NULL;
	next_type = WORD;
	while (mtx[i])
	{
		if (i == 0)
		{
			if (check_type(mtx[i]) != WORD)
			{
				next_type = check_type(mtx[i]);
				i++;
			}
			j = 0;
			list = ft_lstnew();
			list->type = next_type;
			while (mtx[i])
			{
				list->mtx[j] = mtx[i];
				j++;
				i++;
				if (check_type(mtx[i]) != WORD)
				{
					next_type = check_type(mtx[i]);
					i++;
					break;
				}
			}
			list_h = list;
		}
		else
		{
			j = 0;
			list->next = ft_lstnew();
			list->next->type = next_type;
			while (mtx[i])
			{
				list->next->mtx[j] = mtx[i];
				j++;
				i++;
				if (check_type(mtx[i]) != WORD)
				{
					next_type = check_type(mtx[i]);
					i++;
					break;
				}
			}
			list = list->next;
		}
	}
	return (list_h);
} //init_list 05/02/24