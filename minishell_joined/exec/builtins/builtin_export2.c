/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:45:49 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/22 22:45:52 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	loop_add_env(t_env	*current, char *key, char *value, t_shell *shell)
{
	while (current != NULL)
	{
		if (ft_strrncmp(current->name, key, ft_strrlen(key)) == 0
			&& ft_strrlen(current->name) == ft_strrlen(key))
		{
			free(current->content);
			current->content = ft_sstrdup(value);
			if (!current->content)
			{
				perror("strdup");
				builtin_exit(NULL, shell, -1);
			}
			return (1);
		}
		current = current->next;
	}
	return (0);
}

t_env	*more_to_env(t_shell *shell, char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		builtin_exit(NULL, shell, -1);
		exit(EXIT_FAILURE);
	}
	new_node->name = ft_sstrdup(key);
	if (!new_node->name)
	{
		perror("strdup");
		builtin_exit(NULL, shell, -1);
	}
	new_node->content = ft_sstrdup(value);
	if (!new_node->content)
	{
		perror("strdup");
		builtin_exit(NULL, shell, -1);
	}
	new_node->next = NULL;
	return (new_node);
}

/* Añadir o reemplazar variables en t_env */
void	add_to_env(char *key, char *value, t_env **env, t_shell *shell)
{
	t_env	*current;
	t_env	*new_node;
	t_env	*last;
	int		found;

	if (!key || !value || !env)
	{
		write(2, "Error: Argumentos invalidos en add_to_env\n", 44);
		return ;
	}
	current = *env;
	found = loop_add_env(current, key, value, shell);
	if (found)
		return ;
	new_node = more_to_env(shell, key, value);
	if (*env == NULL)
		*env = new_node;
	else
	{
		last = *env;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
}

t_env	*search_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strrncmp(env->name, key, ft_strrlen(key)) == 0
			&& ft_strrlen(env->name) == ft_strrlen(key))
			return (env);
		env = env->next;
	}
	return (NULL);
}
