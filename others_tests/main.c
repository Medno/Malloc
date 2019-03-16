#include "lib_alloc.h"


int	main(void)
{
	char	*str;
	char	*str_bis;
	char	*stra;
	int		i;

	i = 0;
	str = (char *)ft_malloc(sizeof(char) * 10 + 1);
	str_bis = (char *)ft_malloc(sizeof(char) * 5 + 1);
	stra = (char *)malloc(sizeof(char) * 5);
	while (i < 4)
	{
		str[i] = 49 + i;
		str_bis[i] = 50 + i;
		stra[i] = 49 + i;
		i++;
	}
	str[i] = '\0';
	str_bis[i] = '\0';
	stra[i] = '\0';
	ft_putendl(str);
	ft_putendl(str_bis);
	ft_putendl(stra);
	show_alloc_mem();
	return (0);	
}
