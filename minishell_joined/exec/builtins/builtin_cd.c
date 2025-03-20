/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:20:18 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/13 11:20:20 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/* Obtener el valor de una variable en t_env */
char	*get_env_value(t_env *env, const char *varname)
{
	while (env)
	{
		if (exec_ft_strncmp(env->name, varname, exec_ft_strlen(env->name)) == 0
			&& exec_ft_strlen(env->name) == exec_ft_strlen(varname))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

/* Actualizar (o crear) una variable en t_env */
void	update_env_value(t_env **env, const char *varname, const char *new_content)
{
	t_env	*tmp;
	t_env	*new_node;

	tmp = *env;
	while (tmp)
	{
		if (exec_ft_strncmp(tmp->name, varname, exec_ft_strlen(tmp->name)) == 0
			&& exec_ft_strlen(tmp->name) == exec_ft_strlen(varname))
		{
			free(tmp->content);
			tmp->content = ft_sstrdup(new_content);
			return ;
		}
		tmp = tmp->next;
	}
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("update_env_value");
		return ;
	}
	new_node->name = ft_sstrdup(varname);
	new_node->content = ft_sstrdup(new_content);
	new_node->next = *env;
	*env = new_node;
}

/* Expandir la tilde ('~') usando el valor de "HOME" */
static char	*expand_tilde(const char *arg, t_env *env)
{
	const char	*home;
	char		*expanded;
	size_t		len;

	home = get_env_value(env, "HOME");
	if (!home)
	{
		write(2, "cd: HOME not set\n", 17);
		return (NULL);
	}
	if (exec_ft_strncmp(arg, "~", 1) == 0 && exec_ft_strlen(arg) == 1)
		return (ft_sstrdup(home));
	if (exec_ft_strncmp(arg, "~/", 2) == 0)
	{
		len = exec_ft_strlen(home) + exec_ft_strlen(arg + 1) + 1;
		expanded = malloc(len);
		if (!expanded)
		{
			perror("cd");
			return (NULL);
		}
		exec_ft_strlcpy(expanded, home, len);
		exec_ft_strlcat(expanded, arg + 1, len);
		return (expanded);
	}
	return (ft_sstrdup(arg));
}

/* Actualizar OLDPWD y PWD en la lista t_env */
static int	update_pwd_oldpwd(t_env **env, const char *oldpwd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd");
		return (1);
	}
	update_env_value(env, "OLDPWD", oldpwd);
	update_env_value(env, "PWD", cwd);
	free(cwd);
	return (0);
}

/* Manejar "cd -" usando OLDPWD */
static char	*handle_cd_minus(t_env *env)
{
	char	*oldpwd;

	oldpwd = get_env_value(env, "OLDPWD");
	if (!oldpwd)
	{
		write(2, "cd: OLDPWD not set\n", 19);
		return (NULL);
	}
	write(1, oldpwd, exec_ft_strlen(oldpwd));
	write(1, "\n", 1);
	return (oldpwd);
}

/* Implementación del builtin cd usando t_env */
int	builtin_cd(char **args, t_env **env)
{
	char	*oldpwd;
	char	*path;
	char	*expanded;

	oldpwd = getcwd(NULL, 0);
	path = NULL;
	expanded = NULL;
	if (!oldpwd)
	{
		perror("cd");
		return (1);
	}
	if (!args || !args[0])
	{
		path = get_env_value(*env, "HOME");
		if (!path)
		{
			write(2, "cd: HOME not set\n", 17);
			free(oldpwd);
			return (1);
		}
	}
	else if (args[1])
	{
		write(2, "cd: too many arguments\n", 24);
		free(oldpwd);
		return (1);
	}
	else if (exec_ft_strncmp(args[0], "-", 1) == 0 && exec_ft_strlen(args[0]) == 1)
	{
		path = handle_cd_minus(*env);
		if (!path)
		{
			free(oldpwd);
			return (1);
		}
	}
	else
	{
		expanded = expand_tilde(args[0], *env);
		if (!expanded)
		{
			free(oldpwd);
			return (1);
		}
		path = expanded;
	}
	if (chdir(path) == -1)
	{
		perror("cd");
		free(oldpwd);
		free(expanded);
		return (1);
	}
	if (update_pwd_oldpwd(env, oldpwd) != 0)
	{
		free(oldpwd);
		free(expanded);
		return (1);
	}
	free(oldpwd);
	free(expanded);
	return (0);
}
