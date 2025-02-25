/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:40:00 by juan-ant          #+#    #+#             */
/*   Updated: 2023/10/11 21:27:28 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_comp(t_list *list, t_list *to_add, void (*del)(void *))
{
	if (to_add == NULL || to_add->content == NULL)
	{
		if (to_add != NULL)
			free(to_add);
		if (list != NULL)
			ft_lstclear(&list, del);
		return (1);
	}
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*to_add;
	void	*var;

	list = NULL;
	while (lst != NULL)
	{
		var = f(lst->content);
		to_add = ft_lstnew(var);
		if (ft_comp(list, to_add, del) == 1)
		{
			del(var);
			return (0);
		}
		if (list == NULL)
			list = to_add;
		else
			ft_lstadd_back(&list, to_add);
		lst = lst->next;
	}
	return (list);
}
