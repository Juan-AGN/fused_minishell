#include "builtins.h"

int	builtin_cd(char **args)
{
	char	*path;

	if (!args) // Si no se pasa argumento, cambiar a $HOME
	{
		path = getenv("HOME"); // Obtener el valor de la variable de entorno HOME
		if (!path)
		{
			write(2, "cd: HOME not set\n", 17);
			return 1;
		}
	}
	else if (args[1])
	{
		perror("cd: too many arguments");
		return 1;
	}
	else
		path = args[0];
	if(chdir(path) == -1)
	{
		perror("cd");
		return 1;
	}
	return 0;
}