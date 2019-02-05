/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 11:42:52 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/15 16:27:07 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getopt(char **cmd, int *i)
{
	char	*param;

	if (!(param = ft_strdup("")))
		return (NULL);
	while (cmd[*i] && cmd[*i][0] == '-' && ft_strlen(cmd[*i]) != 1)
	{
		param = ft_onejoinf(param, &cmd[*i][1]);
		(*i)++;
		if (cmd[*i] && ft_strcmp(cmd[*i], "--") == 0)
			if ((*i)++)
				break ;
	}
	if (param[0] == '\0')
		ft_strdel(&param);
	return (param);
}
