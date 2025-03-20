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

/* Verificar si un identificador es válido */
int	is_valid_identifier(const char *str)
{
	if (!str || *str == '\0' || !(ft_iisalpha(*str) || *str == '_'))
		return (0);
	str++;
	while (*str)
	{
		if (!(ft_iisalnum(*str) || *str == '_'))
			return (0);
		str++;
	}
	return (1);
}

/* Añadir o reemplazar variables en t_env */
void	add_to_env(char *key, char *value, t_env **env)
{
	t_env	*current;
	t_env	*new_node;
	t_env	*last;

	if (!key || !value || !env)
	{
		write(2, "Error: Argumentos invalidos en add_to_env\n", 44);
		return ;
	}
	current = *env;
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
				exit(EXIT_FAILURE);
			}
			return ;
		}
		current = current->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_node->name = ft_sstrdup(key);
	if (!new_node->name)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	new_node->content = ft_sstrdup(value);
	if (!new_node->content)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	new_node->next = NULL;
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

/* Implementación del comando export */
int	builtin_export(t_token *command, t_env **env)
{
	int		i;
	char	*equal_sign;
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
	i = 0;
	while (i < command->nparams)
	{
		equal_sign = ft_sstrchr(command->params[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			if (is_valid_identifier(command->params[i]))
				add_to_env(command->params[i], equal_sign + 1, env);
			else
			{
				printf("export: `%s': not a valid identifier\n", command->params[i]);
				return_value = 1;
			}
			*equal_sign = '=';
		}
		i++;
	}
	return (return_value);
}
