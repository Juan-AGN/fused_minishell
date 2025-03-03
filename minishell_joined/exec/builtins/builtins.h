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

typedef struct t_shell
{
	struct t_env	**env;
	struct t_token	*token;
	int				ncomands;
	char 			*exit_code;
}	t_shell;

typedef struct t_token
{
	char			*command;
	int				nparams;
	int				ninfiles;
	int				noutfiles;
	char			**params;
	char			**infiles;
	char			**outfiles;
}	t_token;

void	builtin_echo(t_token *command);
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
void	builtin_unset(t_token *command, t_env **env);
void	builtin_export(t_token   *command, t_env **env);

#endif