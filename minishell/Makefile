# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 15:45:00 by clfouger          #+#    #+#              #
#    Updated: 2025/10/16 16:48:32 by cade-jes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g3 -MMD -MP
RM			:= rm -rf

# Directories
OBJ_DIR		:= obj
LIBFT_DIR	:= ./libft
LIBFT_A		:= $(LIBFT_DIR)/libft.a

# Colors
GREEN		:= \033[0;32m
CYAN		:= \033[0;36m
YELLOW		:= \033[0;33m
RED			:= \033[0;31m
RESET		:= \033[0m
BOLD		:= \033[1m

# Sources
SRCS		:= main.c \
			readline/readline.c \
			readline/readline_utils.c \
			builtins/ft_pwd.c \
			builtins/ft_echo.c \
			builtins/ft_cd.c \
			builtins/ft_exit_bi.c \
			builtins/ft_unset.c \
			builtins/ft_built_in.c \
			builtins/env/ft_add_env.c \
			builtins/env/ft_creat_env.c \
			builtins/env/ft_env.c \
			builtins/env/ft_update_env.c \
			builtins/export/ft_add_export.c \
			builtins/export/ft_creat_export.c \
			builtins/export/ft_export.c \
			builtins/export/ft_update_export.c \
			builtins/export/ft_sort_export.c \
			parsing/tokenisation/buffer_validation.c \
			parsing/tokenisation/buffer_validation_utils.c \
			parsing/tokenisation/buffer_validation_utils2.c \
			parsing/tokenisation/get_token.c \
			parsing/tokenisation/split_args.c \
			parsing/tokenisation/split_args_utils.c \
			parsing/tokenisation/split_args_validation.c \
			parsing/tokenisation/lst_parsing.c \
			parsing/cmd_init_parsing.c \
			parsing/cmd_init_parsing_utils.c \
			parsing/cmd_init_parsing_utils2.c \
			parsing/cmd_utils.c \
			parsing/cmd_utils2.c \
			parsing/quotes/token_n_quotes.c \
			parsing/quotes/quote_check_valid.c \
			parsing/quotes/quote_utils.c \
			parsing/expand/expand_var_utils.c \
			parsing/expand/expand_utils.c \
			parsing/expand/expand_utils2.c \
			parsing/expand/expand_n_var.c \
			parsing/expand/expand_n_quotes.c \
			parsing/expand/expand_quotes_utils.c \
			parsing/redirections/redirections.c \
			parsing/redirections/redirections_utils.c \
			parsing/words_parsing.c \
			error/ft_error.c \
			ft_utils/ft_utils_1.c \
			ft_utils/ft_utils_builtins.c \
			ft_utils/signal.c \
			ft_utils/ft_utils_exec.c \
			struct/list_1.c \
			free/ft_free.c \
			free/ft_free2.c \
			exit/ft_exit.c \
			core/find_command.c \
			core/ft_utils.c \
			core/heredoc.c \
			core/pipeline.c \
			core/verif_file.c \
			core/wait.c

OBJS		:= $(SRCS:%.c=$(OBJ_DIR)/%.o)
DEP			:= $(SRCS:%.c=$(OBJ_DIR)/%.d)
TOTAL		:= $(words $(SRCS))
LIBFT_SRC	:= $(shell find $(LIBFT_DIR) -type f \( -name '*.c' -o -name '*.h' -o -name 'Makefile' \))

# Rules
all: $(NAME)

$(LIBFT_A): $(LIBFT_SRC)
	@printf "$(YELLOW)🔧 Compilation de libft...$(RESET)\n"
	@make -C $(LIBFT_DIR) all > /dev/null 2>&1
	@printf "$(GREEN)✔ Libft compilée avec succès$(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ && \
	COUNT=$$(find $(OBJ_DIR) -name "*.o" | wc -l); \
	PERCENT=$$(echo "$$COUNT * 100 / $(TOTAL)" | bc 2>/dev/null || echo "$$(($$COUNT * 100 / $(TOTAL)))"); \
	BARS=$$(echo "$$PERCENT / 5" | bc 2>/dev/null || echo "$$(($$PERCENT / 5))"); \
	LINE=$$(printf "%0.s█" $$(seq 1 $$BARS 2>/dev/null || seq 1 $$BARS)); \
	SPACES=$$(printf "%0.s " $$(seq $$BARS 19 2>/dev/null || seq $$BARS 19)); \
	printf "\r$(CYAN)[%-20s] %3s%% $(RESET)Compilation: %s" "$$LINE$$SPACES" "$$PERCENT" "$(notdir $<)"

$(NAME): $(LIBFT_A) $(OBJS)
	@printf "\n$(YELLOW)🔗 Édition des liens...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@printf "$(GREEN)$(BOLD)✔ $(NAME) compilé avec succès !$(RESET)\n"
	@printf "$(GREEN)✔ Prêt à être utilisé !$(RESET)\n"

clean:
	@printf "$(RED)🧹 Nettoyage des fichiers objets...$(RESET)\n"
	@make -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@$(RM) $(OBJ_DIR)
	@printf "$(GREEN)✔ Nettoyage terminé$(RESET)\n"

fclean: clean
	@printf "$(RED)🗑️  Suppression de $(NAME)...$(RESET)\n"
	@$(RM) $(NAME)
	@printf "$(GREEN)✔ Nettoyage complet terminé$(RESET)\n"

re: 
	@printf "$(YELLOW)🔄 Recompilation complète...$(RESET)\n"
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re

-include $(DEP)
