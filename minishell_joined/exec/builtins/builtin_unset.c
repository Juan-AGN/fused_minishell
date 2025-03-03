#include "builtins.h"

void	remove_from_env(char *key, t_env **env)
{
	t_env	*current;
	t_env	*prev;
	size_t	key_len;

	if (!key || !env || !(*env)) // Verificar que hay algo en la lista
		return;

	current = *env;
	prev = NULL;
	key_len = ft_strrlen(key);
	// Buscar la variable en la lista
	while (current)
	{
		if (ft_strrncmp(current->name, key, key_len) == 0) // Encontramos la variable
		{
			if (prev) // Caso general: eliminar un nodo que no es el primero
				prev->next = current->next;
			else // Caso especial: eliminar el primer nodo
				*env = current->next;

			// Liberar memoria del nodo eliminado
			free(current->name);
			free(current->content);
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}
// Implementación del comando unset
void	builtin_unset(char **args, t_env **env)
{
	int	i;

	if (!args || !env || !*args)
		return ;
	i = 0;
    while (args[i] != NULL)
	{
		remove_from_env(args[i], env);
		i++;
	}
}
