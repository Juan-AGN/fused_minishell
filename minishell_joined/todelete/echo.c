#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

size_t	ft_strlen(const char *str)
{
	unsigned long	n;

	n = 0;
	while (*str)
	{
		n ++;
		str ++;
	}
	return (n);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s ++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_get_env(char *str)
{
	int	i;
	char	*toreturn;

	i = ft_strlen(str) - ft_strlen(ft_strchr(str, ' ') - 1);
	if (i == -1)
		return (NULL);
	toreturn = malloc(i * sizeof(char) + 1);
	toreturn[i + 1] = '\0';
	while (i != -1)
	{
		toreturn[i] = str[i];
		i --;
	}
	return (toreturn);
}

int     ft_echo_single(char *string)
{
	int i;

	i = 1;
	if (ft_strchr(string, 39) == NULL)
	{
		write(1, "(Placeholder)", 26);
		return (0);
	}
	while (*string != '\0')
	{
		if (*string == 39)
			return (i);
		write(1, string, 1);
		i ++;
		string ++;
	}
	return (i);
}

int     ft_echo_double(char *string)
{
	int i;
	char *env;

	i = 1;
	if (ft_strchr(string, '"') == NULL)
	{
		write(1, "(Placeholder)", 26);
		return (0);
	}
	while (*string != '\0')
	{
		if (*string == '"')
			return (i);
		if (*string == '$')
		{
			env = ft_get_env(string + 1);
			printf("%s\n", getenv(env));
			i += ft_strlen(env) + 1;
			string += ft_strlen(env) + 1;
			free(env);
		}
		else
		{
			write(1, string, 1);
			i ++;
			string ++;
		}
	}
	return (i);
}

int	ft_echo(char *string)
{
	while (*string != '\0')
	{
		if (*string == 39)
			string += ft_echo_single(string + 1);
		else if (*string == '"')
			string += ft_echo_double(string + 1);
		else
			write(1, string, 1);
		string ++;
	}
	write(1, "\n", 1);
	return (1);
}

int main(int nargs, char **args, char **env)
{
	ft_echo("Hola que '$PVARIABLEDEPRUEBA\"\" hola' \"$PATH hola '' \"");
	//printf("\nHola que '$PVARIABLEDEPRUEBA\"\" hola' \"$PATH \n\nhola '' \" a ' \"\n");
}
