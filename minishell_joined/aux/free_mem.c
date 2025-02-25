/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:08:54 by juan-ant          #+#    #+#             */
/*   Updated: 2025/01/29 16:39:17 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell	*ft_mass_free(void *value1, void *value2, void *value3, void *value4)
{
	if (value1 != NULL)
		free(value1);
	if (value2 != NULL)
		free(value2);
	if (value3 != NULL)
		free(value3);
	if (value4 != NULL)
		free(value4);
	return (NULL);
}

int	ft_plstclear(t_env **lst)
{
	void	*aux;
	int		n;

	n = ft_plstsize(*lst);
	while (n > 0)
	{
		aux = (*lst)->next;
		if (lst[0]->name != NULL && lst[0] != NULL)
			free(lst[0]->name);
		if (lst[0]->content != NULL && lst[0] != NULL)
			free(lst[0]->content);
		if (lst[0] != NULL)
			free(*lst);
		*lst = aux;
		n --;
	}
	*lst = NULL;
	return (-1);
}
