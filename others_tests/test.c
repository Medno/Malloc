#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
	char *str;
	char *ptr;
	char *tmp;
	int	 i = 0;
	if (!(str = malloc(12)))
		return 0;
	while (i < 10)
	{
		str[i] = 42;
		i++;
	}
	printf("ici str = %s\n", str);
	if (!(ptr = realloc(str, 0)))
		return 0;
	printf("ici ptr = %s\n", ptr);
	if (!(tmp = realloc(str, -12)))
		return 0;
	printf("ici tmp = %s\n", tmp);
}

