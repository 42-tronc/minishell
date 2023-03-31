# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 10:09:37 by arthurasced       #+#    #+#              #
#    Updated: 2023/03/31 11:50:36 by arthurasced      ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = test

LIBFT = libft/libft.a
HEADER = minishell.h
HDR_PARSING = parsing.h

SRCS = src/parsing_tokens.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -I./inc -Wall -Werror -Wextra #-fsanitize=address -g3
RM = rm -rf

all : $(NAME)

%.o : %.c ./inc/$(HEADER) ./inc/$(HDR_PARSING)
	$(CC) $(CFLAGS) -c $< -o $@

lib :
	make -C libft

$(NAME) : lib $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline $(LIBFT) -o $(NAME)


clean : 
	$(RM) $(OBJS)
	make clean -C libft

fclean :
	$(RM) $(NAME)
	make clean
	make fclean -C libft

re : fclean
	make all

norm :
	norminette ./src ./libft

.PHONY : all lib clean fclean re norm
