/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:16:04 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/23 13:08:22 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	char	*tmp_s1;
	char	*tmp_s2;

	tmp_s1 = (char *)s1;
	tmp_s2 = (char *)s2;
	while (*tmp_s1 && *tmp_s2 && (*tmp_s1 == *tmp_s2))
	{
		tmp_s1++;
		tmp_s2++;
	}
	return ((unsigned char)*tmp_s1 - (unsigned char)*tmp_s2);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	char	*tmp_s1;
	char	*tmp_s2;

	tmp_s1 = (char *)s1;
	tmp_s2 = (char *)s2;
	if (!n)
		return (0);
	while ((*tmp_s1 && *tmp_s2) && *tmp_s1 == *tmp_s2 && n - 1 > 0)
	{
		tmp_s1++;
		tmp_s2++;
		n--;
	}
	return ((unsigned char)*tmp_s1 - (unsigned char)*tmp_s2);
}

int	ft_strequ(char const *s1, char const *s2)
{
	const char	*tmp_s1;
	const char	*tmp_s2;

	tmp_s1 = s1;
	tmp_s2 = s2;
	if (s1 && s2)
	{
		if (!ft_strcmp(tmp_s1, tmp_s2))
			return (1);
	}
	return (0);
}

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (!s1 && !s2)
		return (0);
	if (s1 && s2)
		if (!ft_strncmp(s1, s2, n))
			return (1);
	return (0);
}
