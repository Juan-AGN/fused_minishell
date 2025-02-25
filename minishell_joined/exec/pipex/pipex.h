#ifndef PIPEX_H
# define PIPEX_H 

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "gnl/get_next_line.h"

int     ft_strnncmp(const char *s1, const char *s2, size_t n);
size_t  ft_strllcpy(char *restrict dst, const char *restrict src, size_t size);
size_t  ft_strllen(const char *s);
void    *ft_memmcpy(void *dest, const void *src, size_t n);
void    free__array(char **directories);
size_t  ft_strllcat(char *dst, const char *src, size_t size);
char    **ft_ssplit_exec(char const *s, char c);
char    *ft_subbstr(char const *s, unsigned int start, size_t len);
char    *build_full_path(const char *directory, const char *command);
char    **find_directories(char **envp);
void    here_doc_child(char *limiter, int fd);
void    try(char *full_path, char **commands, char **directories, char **envp);
char    **handle_params_allocation(char *command, char **directories);
void    execute(char *command, char **directories, char **envp);
int     check_argc_heredoc(int argc, char **argv);
void    run(char **argv, char **directories, char **envp, int ncom_ishere[2]);
void    create_pipes(int pipes[][2], int ncom);
void    handle_tofile(int *ncom_ishere, char **argv);
void    handle_fromfile(int pipes[][2], int *ncom_ishere, char **argv);
void    redirect(int pipes[][2], int *ncom_ishere, int current, char **argv);
pid_t   forking(int pipes[][2], int *ncom_ishere, char **argv, char ***mix);
void    returning(int *ncom_ishere, pid_t pid);

#endif