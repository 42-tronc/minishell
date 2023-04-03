# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arthurascedu <arthurascedu@student.42ly    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 13:33:54 by croy              #+#    #+#              #
#    Updated: 2023/04/03 10:32:05 by arthurasced      ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

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
BLINK		:= \033[5m
REVERSE		:= \033[7m
HIDDEN		:= \033[8m
STRIKED		:= \033[9m
RESET		:= \033[0m


# ---------- BASIC VARIABLES ----------
CFLAGS := -Wall -Wextra -Werror -I./header
FSANITIZE = -fsanitize=address
RM := rm -rf

LIBFT_DIR := libft/
LIBFT_NAME := $(LIBFT_DIR)libft.a


# --------- PROJECT VARIABLES ---------
NAME := minishell

SRC_FOLDER := src/
SRC = $(addprefix $(SRC_FOLDER), $(SRC_BUILTIN) $(SCR_PARSING))
# SRC = $(addprefix $(SRC_FOLDER), $(SRC_BUILTIN) $(SRC_PRINTF) $(SRC_GNL))
OBJ_DIR := obj/
OBJ = $(subst $(SRC_FOLDER),$(OBJ_DIR),$(SRC:.c=.o))

HEADER := header/minishell.h
DIR_BUILTIN := $(SRC_FOLDER)exec/built-in/
SRC_BUILTIN := echo.c

HDR_PARSING = header/parsing.h
DIR_PARSING := $(SRC_FOLDER)/parsing/
SCR_PARSING := tokens.c parsing.c


# -------------- RECIPES --------------
all: makefolder rsc $(NAME)

$(NAME): $(LIBFT_NAME) $(OBJ)
	${CC} ${CFLAGS} -o $(NAME) $(OBJ) $(LIBFT_NAME) -lreadline
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
	make clean
	make fclean -C libft

re : fclean
	make all

norm :
	norminette ./src ./libft

.PHONY : all lib clean fclean re norm
