/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:21:48 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/13 11:21:49 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	free_and_return_remove(t_env **current)
{
	if (current && *current)
	{
		free((*current)->name);
		free((*current)->content);
		free(*current);
	}
	return ;
}

void	remove_from_env(char *key, t_env **env)
{
	t_env	*current;
	t_env	*prev;
	size_t	key_len;
	size_t	name_len;

	if (!key || !env || !(*env))
		return ;
	key_len = exec_ft_strlen(key);
	current = *env;
	prev = NULL;
	while (current)
	{
		name_len = exec_ft_strlen(current->name);
		if (key_len == name_len
			&& e_ft_strncmp(current->name, key, key_len) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			return (free_and_return_remove(&current));
		}
		prev = current;
		current = current->next;
	}
}

void	builtin_unset(t_token *command, t_env **env)
{
	int	i;

	i = 0;
	while (i < command->nparams)
	{
		remove_from_env(command->params[i], env);
		i++;
	}
}
