# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/16 10:49:49 by clfouger          #+#    #+#              #
#    Updated: 2025/09/11 15:56:05 by clfouger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
INCLUDE_DIR = ./includes
LIBFT_DIR = ./libft

# Headers
HEADERS = -I $(INCLUDE_DIR) -I $(LIBFT_DIR)

# Library flags
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -L$(LIBFT_DIR) -lft -lreadline

# Source files
SRC_FILES = main.c \
			parsing/lst_parsing.c \
			parsing/words_parsing.c \
			builtins/cd.c \
			builtins/echo.c \
			builtins/env.c \
			builtins/pwd.c \
			env/creat_env.c \
			env/update_env.c \
			env/add_env.c \
			error/error.c

# Object files
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
PURPLE = \033[0;35m
RESET = \033[0m

minishell: $(LIBFT) $(OBJ_DIR) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@printf "$(PURPLE)"
	@printf '___  ____           _ _____ _          _ _ \n'
	@printf '|  \\/  (_)         (_)  ___| |        | | |\n'
	@printf '| .  . |_ _ __ ___  _\\ `--.| |__   ___| | |\n'
	@printf '| |\\/| | | '\''_ '\'' _ \\| |`--. \\ '\''_ \\ / _ \\ | |\n'
	@printf '| |  | | | | | | | | /\\__/ / | | |  __/ | |\n'
	@printf '\\_|  |_/_|_| |_| |_|_\\____/|_| |_|\\___|_|_|\n'
	@printf '                                           \n'
	@printf "$(GREEN)Minishell compiled successfully!$(RESET)\n"
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


# ---------------------------------------------------------------------------- #
#   TESTS                                                                      #
# ---------------------------------------------------------------------------- #

		TEST_NAME = test_tokens
		TEST_SRC = tests/main_tokens.c \
				src/parsing/split_args.c \
				src/parsing/lst_parsing.c \
				src/parsing/words_parsing.c \
				src/utils/*.c

		test_tokens: $(LIBFT)
			@echo "$(YELLOW)[INFO] Compiling test: $(TEST_NAME)...$(RESET)"
			$(CC) $(CFLAGS) $(TEST_SRC) $(LIBFT) -lreadline -o $(TEST_NAME)
			@echo "$(GREEN)[INFO] Test binary ready: ./$(TEST_NAME)$(RESET)"



.PHONY: all clean fclean re# Rules
all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/builtins
	@mkdir -p $(OBJ_DIR)/env
	@mkdir -p $(OBJ_DIR)/error

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@printf "$(YELLOW)Object files cleaned!$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@printf "$(RED)$(NAME) removed!$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
