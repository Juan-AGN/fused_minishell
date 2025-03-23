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
	int				cd_checker;
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
int		builtin_cd(char **args, t_env **env, t_shell *shell, int ncomands);
size_t	ft_strrlen(const char *s);
int		ft_strrncmp(const char *s1, const char *s2, size_t n);
void	builtin_pwd(t_shell *shell);
int		builtin_env(int nparams, char **envp);
char	**ft_spplit(char const *s, char c);
void	*ft_meemcpy(void *dest, const void *src, size_t n);
void	free_array(char **directories);
int		builtin_exit(t_token *command, t_shell *shell, int checker);
int		ft_aatoi(const char *nptr);
int		ft_iisdigit(int c);
void	builtin_unset(t_token *command, t_env **env);
int		builtin_export(t_token *command, t_env **env, t_shell *shell);
char	*ft_sstrchr(const char *s, int c);
int		ft_iisalpha(int c);
int		ft_iisalnum(int c);
char	*ft_sstrdup(const char *s1);
void	*ft_ccalloc(size_t count, size_t size);
void	ft_bbzero(void *s, size_t n);
void	*ft_mmemset(void *s, int c, size_t len);
void	ft_free_for_exit(t_shell *minishell);
void	exec_free_all(t_shell *shell);
int		e_ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	exec_ft_strlen(const char *s);
size_t	exec_ft_cpy(char *restrict dst, const char *restrict src, size_t size);
size_t	exec_ft_strlcat(char *dst, const char *src, size_t size);
int		is_valid_identifier(const char *str);
int		loop_add_env(t_env	*current, char *key, char *value, t_shell *shell);
t_env	*more_to_env(t_shell *shell, char *key, char *value);
void	add_to_env(char *key, char *value, t_env **env, t_shell *shell);
t_env	*search_env(t_env *env, char *key);
size_t	e(const char *s);
char	*get_env_value(t_env *env, const char *varname);
t_env	*retorno(t_shell *shell);
void	update_e(t_env **env, char *varname, char *new_content, t_shell *shell);
void	chck_enpanded(char *expanded, t_shell *shell);
char	*check_home(t_env *env);
char	*expand_tilde(const char *arg, t_env *env, t_shell *shell);
int		update_pwd_oldpwd(t_env **env, char *oldpwd, t_shell *shell);
char	*handle_cd_minus(t_env *env);
void	first_cd(char **path, t_env **env, char *oldpwd, t_shell *shell);
void	second_cd(char *oldpwd, t_shell *shell);
void	thrid_cd(char **path, t_env **env, char *oldpwd, t_shell *shell);
int		change_dir(char *path, char *oldpwd, char *expanded, t_shell *shell);
void	final_cd(t_env **env, char *oldpwd, t_shell *shell, char *expanded);
void	check_expand(char *expanded, char *oldpwd, char **path, t_shell *shell);
int		f(const char *s1, const char *s2, size_t n);
void	check_old(char *oldpwd, t_shell *shell);
void	do_concat(char **envp, t_env *tmp, size_t len, int *i);
void	loop_converting(t_env *tmp, char **envp, t_shell *shell);
char	**exec_convert_env_to_array(t_shell *shell);
void	exec_free_array(char **directories);
void	create_pipes(int pipes[][2], int ncom, t_shell *shell);
void	do_token_func(const t_token *token, size_t *total_length);
char	*token_to_str(const t_token *token, t_shell *shell);
int		has_slash(char *str);
void	checkdirec(char *cmd, char *full_path, char **commands, t_shell *shell);
void	try(char *full_path, char **commands, t_shell *shell, char **envp);

#endif
