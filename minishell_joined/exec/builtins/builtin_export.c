/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:21:08 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/13 11:21:09 by luialvar         ###   ########.fr       */
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

void	exp_lo(t_token *command, int *return_value, t_env **env, t_shell *shell)
{
	int		i;
	char	*equal_sign;

	i = 0;
	while (i < command->nparams)
	{
		equal_sign = ft_sstrchr(command->params[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			if (is_valid_identifier(command->params[i]))
				add_to_env(command->params[i], equal_sign + 1, env, shell);
			else
			{
				printf("export: `%s': no valid identify\n", command->params[i]);
				*return_value = 1;
			}
			*equal_sign = '=';
		}
		i++;
	}
}

/* Implementación del comando export */
int	builtin_export(t_token *command, t_env **env, t_shell *shell)
{
	int		return_value;
	t_env	*current;

	return_value = 0;
	if (command->nparams == 0)
	{
		current = *env;
		while (current != NULL)
		{
			printf("declare -x %s=%s\n", current->name, current->content);
			current = current->next;
		}
		return (0);
	}
	exp_lo(command, &return_value, env, shell);
	return (return_value);
}
