#include <stdlib.h>
#include <stdio.h>

int	main()
{
	char	*str;
	char	*tmp;
	int		size;
	int		i;

	i = -1;
	size = 5000;
	puts("Init malloc");
	str = (char *)malloc(size);
	while (++i < size)
		str[i] = '0' + i % 10;
	str[i - 1] = '\0';
	printf("i : %d\n", i);
	printf("strlen : %zu\n", strlen(str));
	tmp = (char *)malloc(6000);
	str = realloc(str, 9000);
	puts(str);
	return (0);
}
