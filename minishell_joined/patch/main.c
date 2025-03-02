#include "../include/minishell.h"

int	ft_search_space(char *str)
{
	while (*str)
	{
		if (*str <= 32)
			str ++;
		else
			return (0);
	}
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*cwd = NULL;
	t_shell	*minishell;
	int ret;

	if(!envp[0])
		return 1;
	(void)argc;
	(void)argv;
	minishell = ft_prepare_values(envp);
	rl_redisplay();
	argc = 0;
	argv = NULL;
	while (1)
	{
		cwd = getcwd(NULL, 0); //determina sola la memoria
		cwd = ft_strjoin(cwd, "~$: ");
		if (cwd != NULL)
			input = readline(cwd);
		else
		{
			free(cwd);
			perror("getcwd() error");
			return 1;
		}
		if (ft_strncmp(input, "exit\0", 5) == 0)
		{
			free(input);
			free(cwd);
			rl_clear_history();
			break;
		}
		if (ft_search_space(input) == 0)
			add_history(input);
		else
			printf("");
		ret = ft_maintoken(minishell, input);
		if (input != NULL && ret == 0)
		{
			handle_shell(minishell);
		}
		ft_free_tokens(minishell, minishell->token);
		free(input);
		free(cwd);
	}
	ft_plstclear(minishell->env);
	free(minishell->env);
	free(minishell->exit_code);
	free(minishell);
	rl_clear_history();
	return 0;
}
