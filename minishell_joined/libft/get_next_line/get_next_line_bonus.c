/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:43:14 by juan-ant          #+#    #+#             */
/*   Updated: 2024/08/13 16:17:18 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*readed[FOPEN_MAX];
	char		*toreturn;
	size_t		i;
	int			end[1];

	end[0] = 0;
	toreturn = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (ft_bnlchr(readed[fd]) == NULL && end[0] != -1)
		readed[fd] = ft_readall(fd, readed[fd], end);
	if (readed[fd] != NULL && end[0] != -1)
	{
		i = ft_bnllen(readed[fd]);
		if (ft_bnlchr(readed[fd]) != NULL)
			i ++;
		toreturn = malloc(sizeof(char) * (i + 1));
	}
	if (end[0] == -1 || toreturn == NULL)
		readed[fd] = ft_bnleing(readed[fd], NULL, NULL);
	if (toreturn != NULL)
		readed[fd] = ft_separate(readed[fd], toreturn);
	return (toreturn);
}

char	*ft_readall(int fd, char *readed, int *end)
{
	char	*currentread;

	currentread = ft_read(fd, end);
	if (currentread == NULL || end[0] == -1 || end[0] == 0)
	{
		ft_bnleing(currentread, NULL, NULL);
		return (readed);
	}
	readed = ft_bnljoin(readed, currentread);
	if (ft_bnlchr(readed) != NULL)
		return (readed);
	return (ft_readall(fd, readed, end));
}

char	*ft_separate(char *str, char *toreturn)
{
	char		*duplicate;
	size_t		i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		toreturn[i] = str[i];
		i ++;
	}
	if (str[i] == '\n')
	{
		toreturn[i] = '\n';
		i ++;
	}
	toreturn[i] = '\0';
	duplicate = ft_bnldup(str + i);
	ft_bnleing(str, NULL, NULL);
	return (duplicate);
}

char	*ft_read(int fd, int *end)
{
	char	*string;

	string = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (string == NULL)
	{
		end[0] = -1;
		return (NULL);
	}
	*end = read(fd, string, BUFFER_SIZE);
	if (*end <= 0)
		return (ft_bnleing(string, NULL, NULL));
	string[*end] = '\0';
	return (string);
}

char	*ft_bnleing(void *s1, void *s2, void *s3)
{
	if (s1 != NULL)
		free(s1);
	s1 = NULL;
	if (s2 != NULL)
		free(s2);
	s2 = NULL;
	if (s3 != NULL)
		free(s3);
	s3 = NULL;
	return (NULL);
}
