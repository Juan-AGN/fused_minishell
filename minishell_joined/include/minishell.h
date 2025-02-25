/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:57:54 by juan-ant          #+#    #+#             */
/*   Updated: 2025/02/25 17:28:44 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>

typedef struct t_shell
{
	struct t_env	**env;
	struct t_token	*token;
	int				ncomands;
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
	char			**params;
	char			**infiles;
	char			**outfiles;
}	t_token;

//start
t_shell		*ft_prepare_values(char **envp);
//end start

//list
int			ft_plstsize(t_env *lst);

t_env		*ft_plstnew(char *name, char *content);

t_env		*ft_plstlast(t_env *lst);

void		ft_plstadd_front(t_env **lst, t_env *new);

void		ft_plstadd_back(t_env **lst, t_env *new);

t_env		*ft_lstadvance(t_env *lst, int i);

char		*ft_plstsearch(t_env *lst, char *name);
//end list

//free
t_shell		*ft_mass_free(void *value1, void *value2, void *value3, void *value4);

int			ft_plstclear(t_env **lst);

void		ft_free_tokens(t_shell *minishell, t_token *token);
//end free

//miscelanious
char		*ft_get_env(char *str);

int			ft_specialchar_if(char c);
//end miscelanious

//token preparation
int ft_maintoken(t_shell *minishell, char *input);
//	aux
int	ft_comands(char *input);

int	ft_count_inout(char *input);

int	ft_inoutcounter(char *input, char tocount);

int	ft_count_token(char *input);

int	ft_specialchar_if(char c);

int	ft_spcharparams_if(char c);

int	ft_params(char *input);

void ft_aux_in(t_shell *minishell, t_token *token, char *input, int i);

void ft_aux_out(t_shell *minishell, t_token *token, char *input, int i);
//	end aux
//end token preparation

//string manip and aux functions
char		*ft_strndup(const char *s1, int n);
//end string mip and aux functions

//double ""
char	*ft_handledoubles(t_shell *minishell, char *str, char *tojoin);
//end of double ""

//single ''
char	*ft_handlesingles(char *str);
//end of single ''

//handle infiles
char    *ft_handle_inf(t_shell  *minishell, char *input);
//end handle infiles

//handle infiles
char    *ft_handle_out(t_shell  *minishell, char *input);
//end handle infiles

//esp envs
char	*ft_strjoinenv(t_shell *minishell, char *tojoin, char *env);

int		ft_return_lenght(char *str);
//end esp envs

//plain text
char	*ft_handleplain(t_shell *minishell, char *str, char *tojoin);
//end plain text

void    handle_shell(t_shell *shell);

#endif