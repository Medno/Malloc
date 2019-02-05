/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmanip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 11:20:39 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/11 16:09:37 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclean(void *str, size_t size)
{
	ft_memdel(&str);
	size = 0;
}

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (lst)
		while (lst)
		{
			(*f)(lst);
			lst = lst->next;
		}
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;

	tmp = NULL;
	if (lst && f)
	{
		tmp = ft_lstnew(lst->content, lst->content_size);
		tmp = (*f)(lst);
		tmp->next = ft_lstmap(lst->next, f);
	}
	return (tmp);
}

t_list	*ft_lstsplit(char const *s, char c)
{
	t_list	*lst;
	size_t	i;
	size_t	len;
	char	*tmp;

	i = 0;
	len = 0;
	lst = NULL;
	if (s && c)
		while (s[i])
		{
			if (s[i] != c)
			{
				len = 0;
				while (s[i + len] != c && s[i + len])
					len++;
				tmp = ft_strsub(s, i, len);
				ft_lstaddlast(&lst, ft_lstnew(tmp, len));
				ft_strdel(&tmp);
				i += len;
			}
			i = (s[i]) ? i + 1 : i;
		}
	return (lst);
}

t_list	*ft_lsttail(t_list *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}
