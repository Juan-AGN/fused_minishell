#include "builtins.h"

// Función auxiliar para verificar si una cadena es numérica
int is_numeric(const char *str) {
	if (!str || *str == '\0')
		return 0;
	if (*str == '-' || *str == '+') // Permite números negativos y positivos
		str++;
	while (*str) {
		if (!ft_iisdigit(*str))
			return 0;
		str++;
	}
	return 1;
}

// Implementación del builtin exit
int builtin_exit(char **args) {
	int exit_code = 0;

	write(STDOUT_FILENO, "exit\n", 5);
	if (!args) 
		exit(0);
	if (is_numeric(args[0])) 
		exit_code = ft_aatoi(args[0]) % 256;
	else 
    {
		write(STDERR_FILENO, "minishell: exit: ", 17);
		write(STDERR_FILENO, args[0], strlen(args[0]));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		exit(2);
	}

	if (args[1]) 
    {
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
		return 1;
	}
	exit(exit_code);
}