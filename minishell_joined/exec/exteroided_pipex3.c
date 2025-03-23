/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exteroided_pipex3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:26:31 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/23 22:26:42 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exteroided.h"

void	inside_loop(char **chain, int i, t_token *token, int *fileout)
{
	*chain = exec_ft_substr(token->inout[i], 3,
			exec_ft_strlen(token->inout[i]) - 3);
	if ((e_ft_strncmp(token->inout[i], ">>", 2)) == 0)
		*fileout = open(*chain, O_WRONLY | O_CREAT
				| O_APPEND, 0644);
	else if (e_ft_strncmp(token->inout[i], "> ", 2) == 0)
		*fileout = open(*chain, O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
}

int	check_han(int *fileout, char **chain, int *filein)
{
	if (*fileout < 0)
	{
		free(*chain);
		perror("error file");
		if (*filein >= 0)
			close(*filein);
		return (1);
	}
	return (0);
}

int	loop_han(char **chain, t_token *token, int *fileout, int *filein)
{
	int	i;

	i = 0;
	while (i < token->ninout)
	{
		inside_loop(chain, i, token, fileout);
		if (check_han(fileout, chain, filein) == 1)
			return (1);
		if ((e_ft_strncmp(token->inout[i], "< ", 2)) == 0)
		{
			*filein = open(*chain, O_RDONLY);
			if (*filein < 0)
			{
				free(*chain);
				perror("error file");
				if (*fileout > 0)
					close(*fileout);
				return (1);
			}
		}
		free(*chain);
		i++;
	}
	return (0);
}

void	second_han(int real, t_token *token, t_shell *shell, int *filein)
{
	if (real > -1 && token->ninfiles > 0)
	{
		if (dup2(real, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc error");
			close(real);
			builtin_exit(NULL, shell, -1);
		}
		close(real);
	}
	else if (real == -1 && token->ninfiles > 0)
	{
		if (dup2(*filein, STDIN_FILENO) == -1)
		{
			perror("dup2 filein error");
			if (*filein >= 0)
				close(*filein);
			builtin_exit(NULL, shell, -1);
		}
		close(*filein);
	}
}

int	han_red(t_shell *shell, t_token *token, int current_ncoma[2], int real)
{
	int		fileout;
	int		filein;
	char	*chain;

	fileout = 0;
	filein = -1;
	first_han(token, current_ncoma, shell);
	if (loop_han(&chain, token, &fileout, &filein) == 1)
		return (1);
	second_han(real, token, shell, &filein);
	if (token->noutfiles > 0)
	{
		if (dup2(fileout, STDOUT_FILENO) == -1)
		{
			perror("dup2 fileout error");
			builtin_exit(NULL, shell, -1);
		}
		close(fileout);
	}
	if (filein >= 0)
		close(filein);
	if (fileout > 0)
		close(fileout);
	return (0);
}
