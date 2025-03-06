#include "../include/minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  ", 1);
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("  ", 0);
		rl_redisplay();
	}
}

void	if_signal(void)
{
	struct sigaction	sig;

	sig.sa_handler = &handler;
	sig.sa_flags = SA_RESTART;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

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
	if (argc == -1 || argv == NULL)
		return 100;
	minishell = ft_prepare_values(envp);
	rl_redisplay();
	if_signal();
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
		if (ft_search_space(input) == 0)
			add_history(input);
		else
			printf("");
		ret = ft_maintoken(minishell, input);
		if (input != NULL && ret == 0 && minishell->error == 0)
		{
			handle_shell(minishell);
		}
		if (minishell->error != 0)
		{
			ft_printf("Error\n");
			minishell->error = 0;
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

/*		printf("a\n");
		int o = 0;
		int u = 0;
		int e = 0;
		int ou = 0;
		if (minishell->token != NULL)
		{
			while (o != minishell->ncomands)
			{
				printf("COMAND %i: %s\n", o, minishell->token[o].command);
				while (u != minishell->token[o].nparams)
				{
					printf("	COMAND %i PARAM %i: %s\n", o, u, minishell->token[o].params[u]);
					u ++;
				}
				if (minishell->token[o].infiles != NULL)
				{
					while (e != minishell->token[o].ninfiles)
					{
						printf("<%i	COMAND %i INFILE %i: %s\n", minishell->token[o].ninfiles, o, e, minishell->token[o].infiles[e]);
						e ++;
					}
				}
				if (minishell->token[o].outfiles != NULL)
				{
					while (ou != minishell->token[o].noutfiles)
					{
						printf(">%i	COMAND %i OUTFILE %i: %s\n", minishell->token[o].noutfiles, o, ou, minishell->token[o].outfiles[ou]);
						ou ++;
					}
				}
				ou = 0;
				if (minishell->token[o].inout != NULL)
				{
					while (ou != minishell->token[o].ninout)
					{
						printf("%i COMAND %i INOUT %i: %s -> ", minishell->token[o].ninout, o, ou, minishell->token[o].inout[ou]);
						ou ++;
					}
					printf("\n");
				}
				ou = 0;
				e = 0;
				u = 0;
				o ++;
			}
		}*/
