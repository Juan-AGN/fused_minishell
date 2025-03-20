/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:08:54 by juan-ant          #+#    #+#             */
/*   Updated: 2025/03/20 16:20:08 by juan-ant         ###   ########.fr       */
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

void	ft_free_for_exit(t_shell *minishell)
{
	ft_free_tokens(minishell, minishell->token);
	if (minishell->env != NULL)
	{
		ft_plstclear(minishell->env);
		free(minishell->env);
	}
	if (minishell->cwd != NULL)
		free(minishell->cwd);
	if (minishell->input != NULL)
		free(minishell->input);
	if (minishell->exit_code != NULL)
		free(minishell->exit_code);
	if (minishell != NULL)
		free(minishell);
	rl_clear_history();
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

char	*ft_free(char *pointer)
{
	free(pointer);
	pointer = NULL;
	return (NULL);
}
