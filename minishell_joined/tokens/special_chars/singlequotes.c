/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singlequotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:00:44 by juan-ant          #+#    #+#             */
/*   Updated: 2025/01/29 16:46:36 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include "../../include/minishell.h"

char	*ft_handlesingles(char *str)
{
	int		i;
	char	*current;

	i = 0;
	while (str[i] != 39 && str[i] != '\0')
		i ++;
	current = malloc(sizeof(char) * (i + 1));
	if (current == NULL)
		return (NULL);
	ft_strlcpy(current, str, i + 1);
	return (current);
}
