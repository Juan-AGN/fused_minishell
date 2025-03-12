#include "builtins.h"

void	builtin_echo(t_token *command)
{
	int		i;
	int		newline;

	i = 0;
	newline = 1;
	if (command->params[i] && ft_strrncmp(command->params[i], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (i < command->nparams)
	{
		write(1, command->params[i], ft_strrlen(command->params[i]));
		if (i < command->nparams - 1)
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}