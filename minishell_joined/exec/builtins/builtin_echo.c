#include "builtins.h"

void	builtin_echo(char **args)
{
	int		i;
	int	no_newline;

	i = 0;
	no_newline = 0;
	if (args[i] && ft_strrncmp(args[i], "-n", 2) == 0)
	{
		no_newline = 1;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strrlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!no_newline)
		write(1, "\n", 1);
}