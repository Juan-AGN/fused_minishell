/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:21:48 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/13 11:21:49 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void remove_from_env(char *key, t_env **env)
{
    t_env   *current;
    t_env   *prev;

    if (!key || !env || !(*env)) // Verificar parámetros
        return;

    current = *env;
    prev = NULL;

    while (current)
    {
        // Comparamos nombre exacto en lugar de usar key_len
        if (strcmp(current->name, key) == 0)
        {
            // Eliminar nodo
            if (prev)
                prev->next = current->next;
            else
                *env = current->next;

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
void builtin_unset(t_token *command, t_env **env)
{
    int i = 0;

    // Recorremos todos los parámetros (ej. unset VAR1 VAR2 VAR3 ...)
    while (i < command->nparams)
    {
        remove_from_env(command->params[i], env);
        i++;
    }
}
