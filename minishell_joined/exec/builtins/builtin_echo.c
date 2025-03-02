#include "builtins.h"

void	builtin_echo(char **args)
{
	int		i;
	int		newline;

	i = 0;
	newline = 1;
	if (args[i] && ft_strrncmp(args[i], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strrlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}