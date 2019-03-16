#include <unistd.h>
#include <stdlib.h>

int	main()
{
	char	*str;
	int		i;
	int		j;
	size_t	alloc;

	i = 0;
	alloc = 1024 * 1024;
	while (i < 100)
	{
		j = 0;
		str = (char *)malloc(alloc);
//		while (j < alloc)
//		{
			str[j] = 48 + j % 10;
//			j++;
//		}
		str = (char *)realloc(str, 1024);
		write(1, str, 1);
		write(1, "\n", 1);
		free(str);
		i++;
	}
}
