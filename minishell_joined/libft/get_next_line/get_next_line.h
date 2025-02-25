/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:40:47 by juan-ant          #+#    #+#             */
/*   Updated: 2024/08/04 17:09:00 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);

char	*ft_separate(char *str, char *toreturn);

char	*ft_gnleing(void *s1, void *s2, void *s3);

char	*ft_read(int fd, int *end);

char	*ft_gnldup(char *s1);

void	ft_gnlcpy(char *dst, char *src);

char	*ft_gnljoin(char *s1, char *s2);

char	*ft_gnlchr(char *s);

char	*ft_readall(int fd, char *readed, int *end);

size_t	ft_gnllen(char *str);

#endif
