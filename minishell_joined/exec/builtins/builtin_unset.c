#include "builtins.h"
/*
void	remove_from_env(char *key, char **envp)
{
	int		i;
	int		j;
	size_t	key_len;

	if (!key || !envp) // Verificar si los punteros son válidos
		return ;
	key_len = ft_strrlen(key);
	i = 0;
	while (envp[i])
	{
		// Buscar la variable con el formato "key="
		if (ft_strrncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			// No liberamos memoria, solo reorganizamos
			j = i;
			while (envp[j])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			envp[j] = NULL; // Final del array
			break ;
		}
		i++;
	}
}
// Implementación del comando unset
void	builtin_unset(char **args, char **envp)
{
	int	i;

	if (!args || !envp)
		return ;
	i = 0;
    while (args[i])
	{
		remove_from_env(args[i], envp);
		i++;
	}
}
*/