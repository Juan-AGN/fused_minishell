/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:12:53 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/23 13:12:57 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/* Obtener el valor de una variable en t_env */
char	*get_env_value(t_env *env, const char *varname)
{
	while (env)
	{
		if (e_ft_strncmp(env->name, varname, exec_ft_strlen(varname)) == 0
			&& exec_ft_strlen(env->name) == exec_ft_strlen(varname))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

t_env	*retorno(t_shell *shell)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("update_e");
		builtin_exit(NULL, shell, -1);
	}
	return (new_node);
}

/* Actualizar (o crear) una variable en t_env */
void	update_e(t_env **env, char *varname, char *new_content, t_shell *shell)
{
	t_env	*tmp;
	t_env	*new_node;

	tmp = *env;
	while (tmp)
	{
		if (e_ft_strncmp(tmp->name, varname, exec_ft_strlen(tmp->name)) == 0
			&& exec_ft_strlen(tmp->name) == exec_ft_strlen(varname))
		{
			free(tmp->content);
			tmp->content = ft_sstrdup(new_content);
			if (!tmp->content)
			{
				perror("malloc error");
				builtin_exit(NULL, shell, -1);
			}
			return ;
		}
		tmp = tmp->next;
	}
	new_node = retorno(shell);
	new_node->name = ft_sstrdup(varname);
	new_node->content = ft_sstrdup(new_content);
	new_node->next = *env;
	*env = new_node;
}

void	chck_enpanded(char *expanded, t_shell *shell)
{
	if (!expanded)
	{
		perror("cd");
		builtin_exit(NULL, shell, -1);
	}
}

char	*check_home(t_env *env)
{
	char	*home;

	home = get_env_value(env, "HOME");
	if (!home)
	{
		write(2, "cd: HOME not set\n", 17);
		return (NULL);
	}
	return (home);
}
