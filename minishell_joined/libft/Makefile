# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 18:44:08 by juan-ant          #+#    #+#              #
#    Updated: 2024/08/04 18:21:47 by juan-ant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror -g

NAME = libft.a

FILES = printf/ft_printf.c printf/ft_putnbr.c printf/ft_putnstr.c printf/ft_putunbase.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c get_next_line/get_next_line_utils_bonus.c get_next_line/get_next_line_bonus.c ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_striteri.c ft_strmapi.c ft_itoa.c ft_split.c ft_strtrim.c ft_strjoin.c ft_substr.c ft_strdup.c ft_calloc.c ft_atoi.c ft_strnstr.c ft_memcmp.c ft_memchr.c ft_strrchr.c ft_strchr.c ft_tolower.c ft_toupper.c ft_strlcat.c ft_strlcpy.c ft_memmove.c ft_memcpy.c ft_bzero.c ft_memset.c ft_strncmp.c ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c

BONUS = ft_lstmap_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstadd_back_bonus.c ft_lstsize_bonus.c ft_lstadd_front_bonus.c ft_lstnew_bonus.c

BON_OBJ = $(BONUS:%.c=%.o)

OBJ = $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rs $(NAME) $(OBJ)

$(OBJ): %.o:%.c
	gcc -c $(FLAGS) $^ -o $@

bonus: $(BON_OBJ) $(OBJ)
	ar -rs $(NAME) $(OBJ) $(BON_OBJ)

$(BON_OBJ): %.o:%.c
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
