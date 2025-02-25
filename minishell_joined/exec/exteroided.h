#ifndef EXTEROIDED_H
# define EXTEROIDED_H

#include "builtins/builtins.h"

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

void    handle_shell(t_shell *shell);


#endif