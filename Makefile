# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: croy <croy@student.42lyon.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 13:33:54 by croy              #+#    #+#              #
#    Updated: 2023/05/18 12:24:52 by croy             ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# --------- GLOBAL VARIABLES ----------
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c # strict bash mode
MAKEFLAGS += --warn-undefined-variables # warn about Make variables that don’t exist
.DELETE_ON_ERROR:


# ------------ FORMATTING -------------
FG_BLACK 			:= \033[30m
FG_RED 				:= \033[31m
FG_GREEN 			:= \033[32m
FG_YELLOW 			:= \033[33m
FG_BLUE 			:= \033[34m
FG_MAGENTA 			:= \033[35m
FG_CYAN 			:= \033[36m
FG_LIGHT_GRAY 		:= \033[37m
FG_DEFAULT 			:= \033[39m
FG_DARK_GRAY 		:= \033[90m
FG_LIGHT_RED 		:= \033[91m
FG_LIGHT_GREEN 		:= \033[92m
FG_LIGHT_YELLOW 	:= \033[93m
FG_LIGHT_BLUE 		:= \033[94m
FG_LIGHT_MAGENTA 	:= \033[95m
FG_LIGHT_CYAN 		:= \033[96m
FG_WHITE 			:= \033[97m
FG_ORANGE 			:= \033[38:5:208m

BG_BLACK 			:= \033[40m
BG_RED 				:= \033[41m
BG_GREEN 			:= \033[42m
BG_YELLOW 			:= \033[43m
BG_BLUE 			:= \033[44m
BG_MAGENTA 			:= \033[45m
BG_CYAN 			:= \033[46m
BG_LIGHT_GRAY 		:= \033[47m
BG_DEFAULT 			:= \033[49m
BG_DARK_GRAY 		:= \033[100m
BG_LIGHT_RED 		:= \033[101m
BG_LIGHT_GREEN 		:= \033[102m
BG_LIGHT_YELLOW 	:= \033[103m
BG_LIGHT_BLUE 		:= \033[104m
BG_LIGHT_MAGENTA 	:= \033[105m
BG_LIGHT_CYAN 		:= \033[106m
BG_WHITE 			:= \033[107m

BOLD		:= \033[1m
DIM			:= \033[2m
ITALIC		:= \033[3m
UNDERLINE	:= \033[4m
REVERT		:= \033[7m
HIDDEN		:= \033[8m
STRIKED		:= \033[9m
RESET		:= \033[0m


# ---------- BASIC VARIABLES ----------
CFLAGS := -Wall -Wextra -Werror -Ilibft/header/ -Iheader/
FSANITIZE = -fsanitize=address -g3
RM := rm -rf

LIBFT_DIR := libft/
LIBFT_NAME := $(LIBFT_DIR)libft.a
USER := $(shell whoami)


# --------- PROJECT VARIABLES ---------
NAME := minishell
HEADER := header/minishell.h

SRC_FOLDER := src/
OBJ_DIR := obj/
# SRC = $(addprefix $(SRC_FOLDER), $(SRC_BUILTIN) $(SRC_EXEC) $(SCR_PARSING))
SRC = $(addprefix $(SRC_FOLDER), $(SRC_BUILTIN) $(SRC_EXEC) $(SRC_UTILS) $(SCR_PARSING))
OBJ = $(subst $(SRC_FOLDER),$(OBJ_DIR),$(SRC:.c=.o))

DIR_UTILS := $(SRC_FOLDER)utils/
SRC_UTILS := minishell.c exec_char.c split_paths.c

DIR_BUILTIN := $(SRC_FOLDER)exec/built-in/
SRC_BUILTIN := utils.c echo.c pwd.c cd.c env.c export.c unset.c

DIR_EXEC := $(SRC_FOLDER)exec/pipes/
SRC_EXEC := fork.c execve.c files.c strjoin_heredoc.c dispatch.c

DIR_PARSING := $(SRC_FOLDER)parsing/
SCR_PARSING := tokens.c tokens2.c parsing.c envp.c envp_lst.c tokens_lst.c dollar.c dollar2.c identification.c identification2.c prepare.c tilde.c

# ifeq ($(USER), maplepy)
# 	SRC_BUILTIN += main.c
# else
# 	SRC += $(addprefix $(SRC_FOLDER), $(SRC_UTILS))
# endif


# -------------- RECIPES --------------
all: makefolder rsc $(NAME)

$(NAME): $(LIBFT_NAME) $(OBJ)
	@echo -e "\n$(BOLD)Hello $(FG_ORANGE)$(USER)$(RESET)"
	${CC} ${CFLAGS} -o $(NAME) $(OBJ) $(LIBFT_NAME) -lreadline
	@echo -e "$(BG_LIGHT_GREEN)Compiled:\t$(RESET) $(FG_WHITE)$(UNDERLINE)$(NAME)$(RESET) has been created."

$(OBJ_DIR)%.o : $(DIR_UTILS)%.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)%.o : $(DIR_BUILTIN)%.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)%.o : $(DIR_EXEC)%.c $(HEADER)
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
	${CC} $(FSANITIZE) ${CFLAGS} -o $(NAME) $(OBJ) $(LIBFT_NAME) -lreadline

run :
	make re
	./$(NAME) $(ARG)

norm :
	norminette ./src ./libft

.PHONY: all rsc makefolder clean fclean re debug norm
