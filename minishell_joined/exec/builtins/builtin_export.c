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

char	*firs_exp_lo(char **equal_sign, t_token *command, int i, t_shell *shell)
{
	char	*original;

	*equal_sign = ft_sstrchr(command->params[i], '=');
	original = ft_sstrdup(command->params[i]);
	if (!original)
	{
		perror("strdup");
		builtin_exit(NULL, shell, -1);
	}
	if (*equal_sign)
		*(*equal_sign) = '\0';
	return (original);
}

void	final_exp_lo(char *equal_sign, char	*original, int *i)
{
	if (equal_sign)
		*equal_sign = '=';
	free(original);
	(*i)++;
}

void	secondexplo(t_token *command, int i, char *original, int *return_value)
{
	if (!is_valid_identifier(command->params[i]))
	{
		write(STDERR_FILENO, "bash: export: `", 15);
		write(STDERR_FILENO, original, exec_ft_strlen(original));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		*return_value = 1;
	}
}

void	exp_lo(t_token *command, int *return_value, t_env **env, t_shell *shell)
{
	int		i;
	char	*equal_sign;
	char	*original;
	t_env	*found;

	i = 0;
	equal_sign = NULL;
	while (i < command->nparams)
	{
		original = firs_exp_lo(&equal_sign, command, i, shell);
		secondexplo(command, i, original, return_value);
		if (is_valid_identifier(command->params[i]))
		{
			if (!equal_sign)
			{
				found = search_env(*env, command->params[i]);
				if (!found)
					add_to_env(command->params[i], "", env, shell);
			}
			else
				add_to_env(command->params[i], equal_sign + 1, env, shell);
		}
		final_exp_lo(equal_sign, original, &i);
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
