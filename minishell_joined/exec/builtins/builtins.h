#ifndef BUILTINS_H
# define BUILTINS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct t_env
{
	char			*name;
	char			*content;
	struct t_env	*next;
}	t_env;

void	builtin_echo(char **args);
void	builtin_cd(char **args);
size_t	ft_strrlen(const char *s);
int     ft_strrncmp(const char *s1, const char *s2, size_t n);
void	builtin_pwd(void);
void	builtin_env(char **envp);
char	**ft_spplit(char const *s, char c);
void	*ft_meemcpy(void *dest, const void *src, size_t n);
void	free_array(char **directories);
void builtin_exit(char **args) ;
int	ft_aatoi(const char *nptr);
int	ft_iisdigit(int c);
void	builtin_unset(char **args, t_env **env);
void	builtin_export(char **args, char ***envp);

#endif