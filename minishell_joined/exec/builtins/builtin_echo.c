#include "builtins.h"

void	builtin_echo(t_token *command)
{
	int		i;
	int		newline;
	int 	j;

	j = 1;
	i = 0;
	newline = 1;
	if (command->nparams == 0)
	{
		write(1, "\n", 1);
		return;
	}
	while (command->params[i] && command->params[i][0] == '-' && command->params[i][1] == 'n')
	{
		while (command->params[i][j] == 'n')
			j++;
		if (command->params[i][j] != '\0')
			break;
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