/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:43:37 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/22 17:08:23 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint8_t	ft_isdir(t_stat sb)
{
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}

uint8_t	ft_isdot(char *path)
{
	if (ft_strcmp(path, ".") == 0 || ft_strcmp(path, "..") == 0)
		return (1);
	return (0);
}

uint8_t	ft_isexe(t_stat stat)
{
	if (stat.st_mode & S_IXUSR)
		return (1);
	if (stat.st_mode & S_IXGRP)
		return (1);
	if (stat.st_mode & S_IXOTH)
		return (1);
	return (0);
}

uint8_t	ft_islink(t_stat stat)
{
	if ((stat.st_mode & S_IFMT) == S_IFLNK)
		return (1);
	return (0);
}

uint8_t	ft_iswsp(char c)
{
	if (c == ' ' || (c > 8 && c < 12))
		return (1);
	return (0);
}
