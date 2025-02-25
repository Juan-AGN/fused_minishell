/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstcontrol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:18:18 by juan-ant          #+#    #+#             */
/*   Updated: 2025/01/20 17:52:41 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_plstsize(t_env *lst)
{
	int	i;

	if (lst == NULL)
		return (0);
	i = 0;
	while (lst != NULL)
	{
		i ++;
		lst = lst->next;
	}
	return (i);
}

t_env	*ft_plstnew(char *name, char *content)
{
	t_env	*list;

	list = malloc(sizeof(t_env));
	if (list == NULL)
		return (0);
	list->name = name;
	list->content = content;
	list->next = NULL;
	return (list);
}

t_env	*ft_plstlast(t_env *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_plstadd_front(t_env **lst, t_env *new)
{
	new->next = lst[0];
	lst[0] = new;
}

void	ft_plstadd_back(t_env **lst, t_env *new)
{
	if (lst[0] != NULL)
		ft_plstlast(lst[0])->next = new;
	else
		lst[0] = new;
}
