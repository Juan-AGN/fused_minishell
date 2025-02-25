/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:43:14 by juan-ant          #+#    #+#             */
/*   Updated: 2024/08/04 17:09:39 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*readed;
	char		*toreturn;
	size_t		i;
	int			end[1];

	end[0] = 0;
	toreturn = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		end[0] = -1;
	if (ft_gnlchr(readed) == NULL && end[0] != -1)
		readed = ft_readall(fd, readed, end);
	if (readed != NULL && end[0] != -1)
	{
		i = ft_gnllen(readed);
		if (ft_gnlchr(readed) != NULL)
			i ++;
		toreturn = malloc(sizeof(char) * i + 1 - ft_gnllen(ft_gnlchr(readed)));
	}
	if (end[0] == -1 || toreturn == NULL)
		readed = ft_gnleing(readed, NULL, NULL);
	if (toreturn != NULL)
		readed = ft_separate(readed, toreturn);
	return (toreturn);
}

char	*ft_readall(int fd, char *readed, int *end)
{
	char	*currentread;

	currentread = ft_read(fd, end);
	if (currentread == NULL || end[0] == -1 || end[0] == 0)
	{
		ft_gnleing(currentread, NULL, NULL);
		return (readed);
	}
	readed = ft_gnljoin(readed, currentread);
	if (ft_gnlchr(readed) != NULL)
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
	duplicate = ft_gnldup(str + i);
	ft_gnleing(str, NULL, NULL);
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
		return (ft_gnleing(string, NULL, NULL));
	string[*end] = '\0';
	return (string);
}

char	*ft_gnleing(void *s1, void *s2, void *s3)
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
