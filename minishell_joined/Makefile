# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/13 16:34:55 by juan-ant          #+#    #+#              #
#    Updated: 2025/02/25 17:45:15 by juan-ant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror -g

BONUS_NAME =

NAME = minishell

FILES = aux/string_aux.c patch/main.c patch/shell_preparation.c list/lstcontrol.c list/lstcontrol_2.c aux/free_mem.c tokens/maintoken.c tokens/auxtokentwo.c tokens/tokenfree.c tokens/auxtoken.c tokens/auxtokenifs.c tokens/special_chars/singlequotes.c tokens/special_chars/doublequotes.c tokens/special_chars/handleplain.c tokens/special_chars/infiles.c tokens/special_chars/outfiles.c

EXEC = exec/exteroided_pipex.c exec/builtins/builtin_cd.c exec/builtins/builtin_echo.c exec/builtins/builtin_env.c exec/builtins/builtin_exit.c exec/builtins/builtin_export.c exec/builtins/builtin_pwd.c exec/builtins/builtin_unset.c exec/builtins/external_functions.c exec/builtins/ft_split.c exec/exec_external_functions.c exec/exec_split.c exec/exec_libft.c exec/gnl.c

OBJ = $(FILES:%.c=%.o)

EXEC_OBJ = $(EXEC:%.c=%.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(EXEC_OBJ) $(LIBFT)
	$(MAKE) -C libft
	cc $(FLAGS) -g -lreadline $(OBJ) $(EXEC_OBJ) $(LIBFT) -o $(NAME)

$(OBJ): %.o:%.c
	clang -c $(FLAGS) $^ -o $@

$(EXEC_OBJ): %.o:%.c
	clang -c $(FLAGS) $^ -o $@

$(LIBFT):
	$(MAKE) -C libft

$(BON_OBJ): %.o:%.c
	clang -c $(FLAGS) $^ -o $@

clean:
	rm -f $(OBJ) $(EXEC_OBJ)
	$(MAKE) clean -C libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all

.PHONY: clean
.PHONY: fclean
.PHONY: re
.PHONY: all
