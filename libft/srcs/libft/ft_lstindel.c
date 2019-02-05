/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstindel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 11:20:39 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/11 11:06:12 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstindel(t_list **first, t_list *del)
{
	t_list	*tmp;

	tmp = NULL;
	if (del == *first)
	{
		if ((*first)->next)
		{
			*first = (*first)->next;
			ft_lstdelone(&del, ft_lstclean);
		}
		else
			ft_lstdel(first, ft_lstclean);
	}
	else
	{
		while (tmp->next && tmp->next != del)
			tmp = tmp->next;
		if (tmp->next)
		{
			tmp->next = del->next;
			ft_lstdelone(&del, ft_lstclean);
		}
	}
}
