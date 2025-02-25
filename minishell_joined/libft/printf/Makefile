# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 18:44:08 by juan-ant          #+#    #+#              #
#    Updated: 2023/11/24 16:01:14 by juan-ant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

FILES = ft_putunbase.c ft_printf.c ft_putnbr.c ft_putnstr.c

OBJ = $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rsc $(NAME) $(OBJ)

$(OBJ): %.o:%.c
	gcc -c $(FLAGS) $^ -o $@

clean:
	rm -f $(OBJ) $(BON_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
.PHONY: fclean
.PHONY: re
.PHONY: all
.PHONY: bonus
