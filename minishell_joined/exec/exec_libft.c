#include "exteroided.h"


size_t	exec_ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (dst[len] && len < size)
		len++;
	while (src[i] && (len + i + 1) < size)
	{
		dst[len + i] = src[i];
		i++;
	}
	if (len < size)
		dst[len + i] = '\0';
	return (len + exec_ft_strlen(src));
}

size_t	exec_ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}


size_t	exec_ft_strlcpy(char *restrict dst, const char *restrict src, size_t size)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = exec_ft_strlen((char *) src);
	if (size != 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

int	exec_ft_strncmp(const char *s1, const char *s2, size_t n)
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

void	*exec_ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!src && !dest)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*exec_ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;

	if (!s)
		return (NULL);
	size = exec_ft_strlen (s);
	if (start >= size)
	{
		sub = malloc (1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (len + start > size)
	{
		len = size - start;
	}
	sub = (char *)malloc (len + 1);
	if (!sub)
		return (NULL);
	exec_ft_memcpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}

char	*exec_ft_strjoin(char const *s1, char const *s2)
{
	char	*retorno;
	size_t	size;

	if (!s1 || !s2)
		return (0);
	size = exec_ft_strlen(s1) + exec_ft_strlen(s2);
	retorno = (char *)malloc(size + 1);
	if (!retorno)
		return (0);
	exec_ft_memcpy(retorno, s1, exec_ft_strlen(s1));
	exec_ft_memcpy(retorno + exec_ft_strlen(s1), s2, exec_ft_strlen(s2));
	retorno[size] = '\0';
	return (retorno);
}

char	*exec_ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	len = exec_ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i++;
	}
	return (NULL);
}

char	*exec_ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*dinamic;

	len = exec_ft_strlen(s1) + 1;
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