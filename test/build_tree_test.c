#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

typedef struct s_args
{
	char	*str;
}		t_args;

int main()
{
	t_args	*args;

	args[0].str = "abc";
	args[1].str = "def";
	args[2].str = "ghi";

	int i = -1;
	printf("test\n");
	while (args)
	{
		printf("args: %s", args->str);
		args++;
	}
}
