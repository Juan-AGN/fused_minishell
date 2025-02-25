/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:39:29 by luialvar          #+#    #+#             */
/*   Updated: 2025/02/25 17:00:23 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strddup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*dinamic;

	len = ft_strllen(s1) + 1;
	i = 0;
	dinamic = (char *)malloc (len);
	if (!dinamic)
		return (NULL);
	while (i < len)
	{
		dinamic [i] = s1 [i];
		i++;
	}
	return (dinamic);
}

int	ft_strnncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

static char	*ft_cpyfile_to_backup(int fd, char *buf, char *backup)
{
	int		read_line;
	char	*temp;

	while (1)
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
			return (0);
		else if (read_line == 0)
			break ;
		buf[read_line] = '\0';
		if (!backup)
			backup = ft_strddup("");
		temp = backup;
		backup = ft_strrjoin(temp, buf);
		free(temp);
		if (ft_strrchr(buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*ft_extract_bytes_after_newline(char *line)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0')
		return (NULL);
	backup = ft_subbstr(line, count + 1, ft_strllen(line) - count - 1);
	if (backup[0] == '\0')
	{
		free(backup);
		backup = NULL;
	}
	line[count + 1] = '\0';
	return (backup);
}

char	*get__next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	line = ft_cpyfile_to_backup(fd, buffer, backup);
	free(buffer);
	if (!line)
	{
		free(backup);
		backup = NULL;
		return (0);
	}
	backup = ft_extract_bytes_after_newline(line);
	if (backup == NULL && (line == NULL || line[0] == '\0'))
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	return (line);
}
