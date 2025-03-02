/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstcontrol_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:56:43 by juan-ant          #+#    #+#             */
/*   Updated: 2025/03/02 13:03:00 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_lstadvance(t_env *lst, int i)
{
	if (lst == NULL)
		return (NULL);
	while (i > 0)
	{
		lst = lst->next;
		i --;
	}
	return (lst);
}

char	*ft_plstsearch(t_env *lst, char *name,  t_shell *minishell)
{
	if (lst == NULL)
		return ("");
	if (ft_strncmp(name, "?", ft_strlen(name)) == 0)
		return (minishell->exit_code);
	while (lst->next != NULL)
	{
		if (ft_strlen(lst->name) == ft_strlen(name))
			if (ft_strncmp(lst->name, name, ft_strlen(name)) == 0)
				return (lst->content);
		lst = lst->next;
	}
	return ("");
}
