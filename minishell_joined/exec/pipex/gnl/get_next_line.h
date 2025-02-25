/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get__next_line6.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:41:57 by luialvar          #+#    #+#             */
/*   Updated: 2025/02/25 16:36:28 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../pipex.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get__next_line(int fd);
char	*ft_strrjoin(char const *s1, char const *s2);
size_t	ft_strllen(const char *s);
char	*ft_strrchr(const char *str, int c);
char	*ft_subbstr(char const *s, unsigned int start, size_t len);
void	*ft_memmcpy(void *dest, const void *src, size_t n);
char	*ft_strddup(const char *s1);
int		ft_strnncmp(const char *s1, const char *s2, size_t n);

#endif
