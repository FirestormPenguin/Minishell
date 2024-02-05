#include "../../include/minishell.h"

int	ft_pwd(void)
{
	char	pwd[4096];

	if (getcwd(pwd, sizeof(pwd)))
		printf("%s\n", pwd);
	else
		printf("minshell: the path is broken");
	
	return(0);
}
