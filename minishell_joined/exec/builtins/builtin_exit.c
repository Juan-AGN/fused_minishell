/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:20:58 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/13 11:20:59 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_numeric(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_iisdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	additional_exit(char **args, t_shell *shell, int *exit_code)
{
	if (!args)
	{
		exec_free_all(shell);
		exit(0);
	}
	if (is_numeric(args[0]))
		*exit_code = ft_aatoi(args[0]) % 256;
	else
	{
		write(STDERR_FILENO, "minishell: exit: ", 17);
		write(STDERR_FILENO, args[0], ft_strrlen(args[0]));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		exec_free_all(shell);
		exit(2);
	}
}

// Implementación del builtin exit
int	builtin_exit(t_token *command, t_shell *shell, int checker)
{
	int	exit_code;

	exit_code = 0;
	if (checker < 0)
	{
		if (isatty(STDOUT_FILENO))
			write(STDOUT_FILENO, "exit\n", 5);
		additional_exit(command->params, shell, &exit_code);
		if (command->nparams > 1)
		{
			write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
			return (1);
		}
		exec_free_all(shell);
		exit(exit_code);
	}
	else
	{
		exec_free_all(shell);
		exit(checker);
	}
}
