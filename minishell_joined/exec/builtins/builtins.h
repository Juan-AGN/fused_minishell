/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:21:33 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/13 11:21:34 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct t_shell
{
	struct t_env	**env;
	struct t_token	*token;
	int				ncomands;
	char			*exit_code;
	char			*input;
	char			*cwd;
	int				error;
	char			**envp;
	char			**directories;
	int				(*pipes)[2];
}	t_shell;

typedef struct t_env
{
	char			*name;
	char			*content;
	struct t_env	*next;
}	t_env;

typedef struct t_token
{
	char			*command;
	int				nparams;
	int				ninfiles;
	int				noutfiles;
	int				ninout;
	char			**params;
	char			**infiles;
	char			**outfiles;
	char			**inout;
}	t_token;

void	builtin_echo(t_token *command);
int		builtin_cd(char **args, t_env **env);
size_t	ft_strrlen(const char *s);
int		ft_strrncmp(const char *s1, const char *s2, size_t n);
void	builtin_pwd(t_shell *shell);
int		builtin_env(int nparams, char **envp);
char	**ft_spplit(char const *s, char c);
void	*ft_meemcpy(void *dest, const void *src, size_t n);
void	free_array(char **directories);
int		builtin_exit(char **args, t_shell *shell, int checker);
int		ft_aatoi(const char *nptr);
int		ft_iisdigit(int c);
void	builtin_unset(t_token *command, t_env **env);
int		builtin_export(t_token *command, t_env **env);
char	*ft_sstrchr(const char *s, int c);
int		ft_iisalpha(int c);
int		ft_iisalnum(int c);
char	*ft_sstrdup(const char *s1);
void	*ft_ccalloc(size_t count, size_t size);
void	ft_bbzero(void *s, size_t n);
void	*ft_mmemset(void *s, int c, size_t len);
void	ft_free_for_exit(t_shell *minishell);
void	exec_free_all(t_shell *shell);
int		exec_ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	exec_ft_strlen(const char *s);
size_t	exec_ft_strlcpy(char *restrict dst, const char *restrict src, size_t size);
size_t	exec_ft_strlcat(char *dst, const char *src, size_t size);

#endif
