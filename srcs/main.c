#include "lib_alloc.h"


int	main(void)
{
	char	*str;
	char	*stra;
	int		i;

	i = 0;
	str = (char *)ft_malloc(sizeof(char) * 5);
	stra = (char *)malloc(sizeof(char) * 5);
	while (i < 4)
	{
		str[i] = 49 + i;
		stra[i] = 49 + i;
		i++;
	}
	str[i] = '\0';
	stra[i] = '\0';
	ft_putendl(str);
	ft_putstr(stra);

	return (0);	
}
