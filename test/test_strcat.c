#include <string.h>
#include <stdio.h>

int main()
{
	char path[50] = "/bin/";
	char tmp_str[50] = "cat";

	printf ("path: %s\n", path);
	printf ("str: %s\n", tmp_str);
	strcat(path, tmp_str);
	printf ("strcat: %s\n", path);
}
