#include "../include/minishell.h"

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  ", 1);
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("  ", 0);
		rl_redisplay();
	}
}

void	handler_two(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("  ", 0);
		rl_redisplay();
	}
}

void	ft_signal(void)
{
	struct sigaction	signal;

	signal.sa_handler = &handler;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
}

int	ft_search_space(char *str)
{
	while (*str)
	{
		if (*str <= 32 && *str >= 1)
			str ++;
		else
			return (0);
	}
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	char	*cwd = NULL;
	t_shell	*minishell;
	int ret;

	if(!envp[0])
		return 1;
	if (argc == -1 || argv == NULL)
		return 100;
	minishell = ft_prepare_values(envp);
<<<<<<< HEAD
	minishell->input = NULL;
=======
	minishell->envp = NULL;
	minishell->pipes = NULL;
	minishell->exit_code = NULL;
>>>>>>> 48f340169af2965b96e79eefe0a5024b979c05b4
	rl_redisplay();
	while (1)
	{
		ft_signal();
		cwd = getcwd(NULL, 0); //determina sola la memoria
		minishell->cwd = ft_strjoin(cwd, "~$: ");
		if (minishell->cwd != NULL)
		{
			while (!minishell->input)
				minishell->input = readline(minishell->cwd);
		}
		else
		{
			free(cwd);
			perror("getcwd() error");
			return 1;
		}
		if (ft_search_space(minishell->input) == 0)
			add_history(minishell->input);
		else
			printf("");
		free(cwd);
		ret = ft_maintoken(minishell, minishell->input);
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, &handler_two);
		if (minishell->input != NULL && ret == 0 && minishell->error == 0)
			handle_shell(minishell);
		if (minishell->error == -5)
		{
			ft_free_for_exit(minishell);
			ft_printf("Malloc error\n");
			exit(-5);
		}
		if (minishell->error != 0)
		{
			ft_printf("Quote error\n");
			minishell->error = 0;
		}
		ft_free_tokens(minishell, minishell->token);
		free(minishell->input);
		minishell->input = NULL;
		free(minishell->cwd);
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
