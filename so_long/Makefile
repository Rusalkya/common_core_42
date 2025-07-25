# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 16:21:47 by clfouger          #+#    #+#              #
#    Updated: 2025/07/21 16:12:56 by clfouger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I . -I ./includes -g

LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux
SRC_DIR = ./src

LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

SRCS =		main.c \
			map/map.c \
			map/map_checking.c \
			map/maped.c \
			controls.c \
			control_player.c \
			display/display.c \
			display/display_player.c \
			display/display_villain.c \
			display/display_map.c \
			cleaning.c \
			verif.c
			
OBJS = $(SRCS:.c=.o)
HEADERS = -I . \
          -I ./includes \
          -I $(LIBFT_DIR) \
          -I $(MLX_DIR)

MLX_FLAGS = -L $(MLX_DIR) -lmlx_Linux -L /usr/X11/lib -lXext -lX11 -lm
RM = rm -f

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
PURPLE = \033[0;35m
RESET = \033[0m

MLX_REPO = https://github.com/42Paris/minilibx-linux.git

all: $(LIBFT) $(MLX_LIB) $(NAME)
	@echo "$(GREEN)[INFO] Compilation completed successfully.$(RESET)"
	@echo "$(PURPLE)"
	@echo " .oooooo..o   .oooooo.               ooooo          .oooooo.   ooooo      ooo   .oooooo.    "
	@echo "d8P'    \`Y8  d8P'  \`Y8b              \`888'         d8P'  \`Y8b  \`888b.     \`8'  d8P'  \`Y8b   "
	@echo "Y88bo.      888      888              888         888      888  8 \`88b.    8  888           "
	@echo " \`\"Y8888o.  888      888              888         888      888  8   \`88b.  8  888           "
	@echo "     \`\"Y88b 888      888              888         888      888  8     \`88b.8  888     ooooo "
	@echo "oo     .d8P \`88b    d88'              888       o \`88b    d88'  8       \`888  \`88.    .88'  "
	@echo "8\"\"88888P'   \`Y8bood8P'  ooooooooooo o888ooooood8  \`Y8bood8P'  o8o        \`8   \`Y8bood8P'   "
	@echo "$(RESET)"
	@echo "$(GREEN)[INFO] BON JEU !$(RESET)"

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "$(YELLOW)[INFO] MinilibX not found, cloning...$(RESET)"; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	@echo "$(YELLOW)[INFO] Compiling MinilibX...$(RESET)"
	@make -C $(MLX_DIR)

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
	@echo "$(RED)[INFO] Cleaning up object files...$(RESET)"
	@make -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean; fi
	$(RM) $(OBJS)

fclean: clean
	@echo "$(RED)[INFO] Removing executable and libraries...$(RESET)"
	@rm -rf minilibx-linux
	@make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re