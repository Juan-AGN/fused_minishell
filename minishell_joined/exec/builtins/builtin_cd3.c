/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:13:13 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/23 13:13:15 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/* Expandir la tilde ('~') usando el valor de "HOME" */
char	*expand_tilde(const char *arg, t_env *env, t_shell *shell)
{
	const char	*home;
	char		*expanded;
	size_t		len;

	if (e_ft_strncmp(arg, "~", 1) == 0 && exec_ft_strlen(arg) == 1)
	{
		home = check_home(env);
		if (!home)
			return (NULL);
		return (ft_sstrdup(home));
	}
	if (e_ft_strncmp(arg, "~/", 2) == 0)
	{
		home = check_home(env);
		if (!home)
			return (NULL);
		len = exec_ft_strlen(home) + exec_ft_strlen(arg + 1) + 1;
		expanded = malloc(len);
		chck_enpanded(expanded, shell);
		exec_ft_cpy(expanded, home, len);
		exec_ft_strlcat(expanded, arg + 1, len);
		return (expanded);
	}
	return (ft_sstrdup(arg));
}

/* Actualizar OLDPWD y PWD en la lista t_env */
int	update_pwd_oldpwd(t_env **env, char *oldpwd, t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd");
		builtin_exit(NULL, shell, -1);
	}
	update_e(env, "OLDPWD", oldpwd, shell);
	update_e(env, "PWD", cwd, shell);
	free(cwd);
	return (0);
}

/* Manejar "cd -" usando OLDPWD */
char	*handle_cd_minus(t_env *env)
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

void	first_cd(char **path, t_env **env, char *oldpwd, t_shell *shell)
{
	*path = get_env_value(*env, "HOME");
	if (!(*path))
	{
		write(2, "cd: HOME not set\n", 17);
		free(oldpwd);
		shell->cd_checker = 1;
		return ;
	}
	shell->cd_checker = 0;
	return ;
}

void	check_old(char *oldpwd, t_shell *shell)
{
	if (!oldpwd)
	{
		perror("cd");
		builtin_exit(NULL, shell, -1);
	}
}
