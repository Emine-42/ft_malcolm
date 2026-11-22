# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macheuk- <macheuk-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/17 16:42:19 by macheuk-          #+#    #+#              #
#    Updated: 2026/11/22 11:18:43 by macheuk-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_malcolm

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

INCLUDES	= -Iincludes -I$(LIBFT_DIR)

SRCS_DIR	= srcs
SRCS		= $(SRCS_DIR)/main.c \
			  $(SRCS_DIR)/utils.c \
			  $(SRCS_DIR)/net.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "\033[32m[make] Executable compilé : $(NAME)\033[0m"

clean:
	@make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)
	@echo "\033[33m[make clean] Objets \".o\" supprimés\033[0m"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	@echo "\033[31m[make fclean] Executable supprimé\033[0m"

re: fclean all

.PHONY: all clean fclean re


.PHONY: all clean fclean re