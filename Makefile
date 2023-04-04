# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 13:33:54 by croy              #+#    #+#              #
#    Updated: 2023/04/04 10:26:30 by croy             ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# --------- GLOBAL VARIABLES ----------
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c # strict bash mode
MAKEFLAGS += --warn-undefined-variables # warn about Make variables that don’t exist
.DELETE_ON_ERROR:


# ------------ FORMATTING -------------
FG_RED 				:= \033[31m
FG_GREEN 			:= \033[32m
FG_DEFAULT 			:= \033[39m
FG_LIGHT_RED 		:= \033[91m
FG_LIGHT_GREEN 		:= \033[92m

BG_RED 				:= \033[41m
BG_GREEN 			:= \033[42m
BG_LIGHT_GREEN 		:= \033[102m

BOLD		:= \033[1m
ITALIC		:= \033[3m
UNDERLINE	:= \033[4m
RESET		:= \033[0m


# ---------- BASIC VARIABLES ----------
CFLAGS := -Wall -Wextra -Werror -Ilibft/header/ -Iheader/ -lreadline
FSANITIZE = -fsanitize=address -g3
RM := rm -rf

LIBFT_DIR := libft/
LIBFT_NAME := $(LIBFT_DIR)libft.a


# --------- PROJECT VARIABLES ---------
NAME := minishell
HEADER := header/minishell.h

SRC_FOLDER := src/
OBJ_DIR := obj/
# SRC = $(addprefix $(SRC_FOLDER), $(SRC_BUILTIN) $(SCR_PARSING))
SRC = $(addprefix $(SRC_FOLDER), $(SRC_BUILTIN))
OBJ = $(subst $(SRC_FOLDER),$(OBJ_DIR),$(SRC:.c=.o))

DIR_BUILTIN := $(SRC_FOLDER)exec/built-in/
SRC_BUILTIN := echo.c pwd.c cd.c

DIR_PARSING := $(SRC_FOLDER)parsing/
SCR_PARSING := tokens.c parsing.c


# -------------- RECIPES --------------
all: makefolder rsc $(NAME)

$(NAME): $(LIBFT_NAME) $(OBJ)
	${CC} ${CFLAGS} -o $(NAME) $(OBJ) $(LIBFT_NAME)
	@echo -e "$(BG_LIGHT_GREEN)Compiled:\t$(RESET) $(FG_WHITE)$(UNDERLINE)$(NAME)$(RESET) has been created."

$(OBJ_DIR)%.o : $(DIR_BUILTIN)%.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)%.o : $(DIR_PARSING)%.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

rsc:
	@$(MAKE) -sC $(LIBFT_DIR)

makefolder :
	@mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_DIR)
	@$(MAKE) $@ -sC $(LIBFT_DIR)
	@echo -e "$(FG_RED)Clean:\t\t $(FG_LIGHT_GRAY)$(ITALIC)$(NAME) object files$(RESET) have been deleted"

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) $@ -sC $(LIBFT_DIR)
	@echo -e "$(FG_RED)FClean:\t\t $(FG_LIGHT_GRAY)$(UNDERLINE)$(NAME)$(RESET) has been deleted."

re: fclean
	@$(MAKE) rsc
	@$(MAKE) all

debug: makefolder rsc $(LIBFT_NAME) $(OBJ)
	${CC} $(FSANITIZE) ${CFLAGS} -o $(NAME) $(OBJ) $(LIBFT_NAME)

run :
	make re
	./$(NAME) $(ARG)

norm :
	norminette ./src ./libft

.PHONY: all rsc makefolder clean fclean re debug norm
