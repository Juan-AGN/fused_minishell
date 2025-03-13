/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:19:25 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/13 11:19:27 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exteroided.h"

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
			backup = exec_ft_strdup("");
		temp = backup;
		backup = exec_ft_strjoin(temp, buf);
		free(temp);
		if (exec_ft_strchr(buf, '\n'))
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
	backup = exec_ft_substr(line, count + 1, exec_ft_strlen(line) - count - 1);
	if (backup[0] == '\0')
	{
		free(backup);
		backup = NULL;
	}
	line[count + 1] = '\0';
	return (backup);
}

char	*exec_get_next_line(int fd)
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
