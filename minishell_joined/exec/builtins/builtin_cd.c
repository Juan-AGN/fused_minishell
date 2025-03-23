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

int	change_dir(char *path, char *oldpwd, char *expanded, t_shell *shell)
{
	if (path)
	{
		if (chdir(path) == -1)
		{
			perror("cd");
			free(oldpwd);
			free(expanded);
			shell->cd_checker = 1;
			return (1);
		}
	}
	return (0);
}

void	final_cd(t_env **env, char *oldpwd, t_shell *shell, char *expanded)
{
	update_pwd_oldpwd(env, oldpwd, shell);
	free(oldpwd);
	free(expanded);
}

void	check_expand(char *expanded, char *oldpwd, char **path, t_shell *shell)
{
	if (!expanded)
	{
		free(oldpwd);
		shell->cd_checker = 1;
		return ;
	}
	*path = expanded;
}

int	f(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

/* Implementación del builtin cd usando t_env */
int	builtin_cd(char **args, t_env **env, t_shell *shell, int ncomands)
{
	char	*oldpwd;
	char	*path;
	char	*expanded;

	oldpwd = getcwd(NULL, 0);
	check_old(oldpwd, shell);
	path = NULL;
	expanded = NULL;
	if (!args || !args[0])
		first_cd(&path, env, oldpwd, shell);
	if (shell->cd_checker == -1 && ncomands > 1)
		second_cd(oldpwd, shell);
	if (shell->cd_checker == -1 && f(args[0], "-", 1) == 0 && e(args[0]) == 1)
		thrid_cd(&path, env, oldpwd, shell);
	if (shell->cd_checker == -1)
	{
		expanded = expand_tilde(args[0], *env, shell);
		check_expand(expanded, oldpwd, &path, shell);
	}
	if (shell->cd_checker == 1)
		return (1);
	if (change_dir(path, oldpwd, expanded, shell))
		return (1);
	final_cd(env, oldpwd, shell, expanded);
	return (0);
}
