#ifndef EXTEROIDED_H
# define EXTEROIDED_H

#include "builtins/builtins.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct t_return
{
	pid_t		pid;
	int 		return_value;
	int			use_pid;
}	t_return;

void    handle_shell(t_shell *shell);
size_t	exec_ft_strlen(const char *s);
size_t	exec_ft_strlcat(char *dst, const char *src, size_t size);
void	exec_free_array(char **directories);
char **exec_convert_env_to_array(t_shell *shell);
void	create_pipes(int pipes[][2], int ncom);
char	**exec_split(char const *s, char c);
t_return	forking(int pipes[][2], t_shell *shell, char **directories, char **envp);
int	returning(int ncom, pid_t pid);
char	**find_directories(char **envp);
int		redirect(int pipes[][2], t_token *token, int current, int ncomands);
void	execute(char *command, char **directories, char **envp);
char	*build_full_path(const char *directory, const char *command);
size_t	exec_ft_strlcpy(char *restrict dst, const char *restrict src, size_t size);
int		exec_ft_strncmp(const char *s1, const char *s2, size_t n);
void	*exec_ft_memcpy(void *dest, const void *src, size_t n);
void	here_doc_child(char *limiter, int fd);
char	*exec_ft_substr(char const *s, unsigned int start, size_t len);
char	*exec_ft_strdup(const char *s1);
char	*exec_ft_strchr(const char *s, int c);
char	*exec_ft_strjoin(char const *s1, char const *s2);
char	*exec_get_next_line(int fd);
char	*ft_itoa(int n);
int is_builtin(char *builtin);
int	execute_builtin(t_token   *command, char ** envp, t_env **env);

#endif