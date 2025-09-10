# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/16 10:49:49 by clfouger          #+#    #+#              #
#    Updated: 2025/08/16 12:01:59 by clfouger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I . -I ./includes -g

LIBFT_DIR = ./libft
SRC_DIR = ./src

LIBFT = $(LIBFT_DIR)/libft.a

SRCS =		src/main.c \
			src/parsing/lst_parsing.c \
			src/parsing/words_parsing.c \
			src/readinput.c \
			
OBJS = $(SRCS:.c=.o)
HEADERS = -I . \
          -I ./includes \
          -I $(LIBFT_DIR) \

RM = rm -f

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
PURPLE = \033[0;35m
RESET = \033[0m

mimishell:
	@printf "$(PURPLE)"
	@printf '___  ____           _ _____ _          _ _ \n'
	@printf '|  \\/  (_)         (_)  ___| |        | | |\n'
	@printf '| .  . |_ _ __ ___  _\\ `--.| |__   ___| | |\n'
	@printf '| |\\/| | | '\''_ '\'' _ \\| |`--. \\ '\''_ \\ / _ \\ | |\n'
	@printf '| |  | | | | | | | | /\\__/ / | | |  __/ | |\n'
	@printf '\\_|  |_/_|_| |_| |_|_\\____/|_| |_|\\___|_|_|\n'
	@printf '                                           \n'
	@printf '                                           \n'
	@printf "$(RESET)"


$(LIBFT):
	@echo "$(YELLOW)[INFO] Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@echo "$(YELLOW)[INFO] Linking objects...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) $(HEADERS) -o $(NAME)

%.o: %.c
	@echo "$(YELLOW)[INFO] Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@echo "$(RED)[INFO] Cleaning up object files...........$(RESET)"
	@make -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean; fi
	$(RM) $(OBJS)

fclean: clean
	@echo "$(RED)[INFO] Cleaning remaining files...............$(RESET)"
	@make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re