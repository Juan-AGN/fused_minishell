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
/* hay que tener en cuenta que tendriamos que imprimir tambien el nombre de
usuario y de la maquina como lo hace la prompt original para eso hay que
coger variables del PATH y otras cosas, ademas hay que ver cuando se imprime
el $ y cuando el # cuando este en modo administrador, esto es solo una aprox*/

//printf("%s@minishell42:%s~$ ", getenv("USER"), cwd);

/*FOR CHECKING ENVS: 		printf("\n %i ENV ORIGINAL | %s |", argc, envp[argc]);
*/
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
		/*
		if (input[0] != 'e' && input[1] != 'x')
		{
			ft_maintoken(minishell, input);
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
				e = 0;
				u = 0;
				o ++;
			}
		}
		}*/
	//	printf("%s\n", ft_handleplain(minishell, input, NULL));
	//	printf("%s\n", ft_handledoubles(minishell, input, NULL));
	//	printf("%s\n", ft_handlesingles(input));
		ft_free_tokens(minishell, minishell->token);
		free(input);
		free(cwd);
	}
	ft_plstclear(minishell->env);
	free(minishell->env);
	free(minishell);
	rl_clear_history();
	return 0;
}
