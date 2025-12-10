# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/05 09:49:46 by clfouger          #+#    #+#              #
#    Updated: 2025/12/01 15:06:10 by cade-jes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CC			=	cc

MAKEFLAGS	+=	--no-print-directory
.SILENT:

GREEN		=	\033[0;32m
CYAN		=	\033[0;36m
YELLOW		=	\033[0;33m
RED			=	\033[0;31m
RESET		=	\033[0m
BOLD		=	\033[1m

SRCS		=	srcs/main.c \
				srcs/other/exit.c \
				srcs/other/list.c \
				srcs/other/msg.c \
				srcs/other/init.c \
				srcs/display/frame.c \
				srcs/movement/movement.c \
				srcs/movement/movement_utils.c \
				srcs/display/raycasting.c \
				srcs/other/utils.c \
				srcs/other/list_2.c \
				srcs/display/draw_wall.c \
				srcs/parsing/images.c \
				srcs/parsing/colors.c \
				srcs/parsing/map_checking.c \
				srcs/parsing/map_validation.c \
				srcs/parsing/flood_fill.c \
				srcs/parsing/read_map.c \
				srcs/parsing/read_map_utils.c \
				srcs/parsing/map_parsing.c \
				srcs/parsing/textures_parsing.c \
				srcs/parsing/init_player.c \
				srcs/parsing/parsing.c

CFLAGS		=	-Wall -Wextra -Werror -g3
CPPFLAGS	=	-MMD -MP -I./includes -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS		=	-L$(LIBFT_DIR) -L$(MLX_DIR) -L/usr/X11/lib
LDLIBS		=	-lft -lmlx_Linux -lXext -lX11 -lm -lreadline

OBJ_DIR		=	obj
LIBFT_DIR	=	./libft
MLX_DIR		=	./minilibx-linux
LIBFT		=	$(LIBFT_DIR)/libft.a
MLX_LIB		=	$(MLX_DIR)/libmlx_Linux.a

OBJS		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
DEPS		=	$(OBJS:.o=.d)

SRC_COUNT	=	$(words $(SRCS))
TOTAL		=	$(shell expr $(SRC_COUNT) + 3)

PRG	=	COUNT=$$(find $(OBJ_DIR) -name "*.o" 2>/dev/null | wc -l); \
		if [ -f "$(LIBFT)" ]; then COUNT=$$((COUNT+1)); fi; \
		if [ -f "$(MLX_LIB)" ]; then COUNT=$$((COUNT+1)); fi; \
		PERCENT=$$(( 100 * $$COUNT / $(TOTAL) )); \
		BARS=$$(( $$PERCENT / 5 )); \
		LINE=$$(printf "%0.s█" $$(seq 1 $$BARS 2>/dev/null)); \
		printf "\r$(CYAN)[%-20s] %3s%% $(RESET)%s" "$$LINE" "$$PERCENT" "$$PROGRESS_LABEL"

PRG_AFTER_LINK	=	LINE=$$(printf "%0.s█" $$(seq 1 20)); \
					printf "\r$(CYAN)[%-20s] 100%% $(RESET)%s\n" "$$LINE" "$$PROGRESS_LABEL"

MLX_REPO	=	https://github.com/42Paris/minilibx-linux.git

RM			=	rm -f
RMDIR		=	rm -rf

all: $(LIBFT) $(MLX_LIB) $(NAME)

$(LIBFT): $(shell find $(LIBFT_DIR) -type f \( -name '*.c' -o -name '*.h' -o -name 'Makefile' \))
	$(MAKE) -C $(LIBFT_DIR) all >/dev/null
	PROGRESS_LABEL="Compilation: libft"; $(PRG)

$(MLX_LIB):
	if [ ! -d "$(MLX_DIR)" ]; then \
		git clone -q $(MLX_REPO) $(MLX_DIR) >/dev/null; \
	fi
	$(MAKE) -C $(MLX_DIR) >/dev/null
	PROGRESS_LABEL="Compilation: minilibx"; $(PRG)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ >/dev/null
	PROGRESS_LABEL="Compilation: $(notdir $<)"; $(PRG)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME) >/dev/null
	PROGRESS_LABEL="Link: $(NAME)"; $(PRG_AFTER_LINK)
	printf "$(GREEN)$(BOLD)✔ $(NAME) compilé avec succès !$(RESET)\n"
	printf "$(GREEN)✔ Prêt à être utilisé !$(RESET)\n"

clean:
	@printf "$(RED)🧹 Nettoyage des fichiers objets...$(RESET)\n"
	$(MAKE) -C $(LIBFT_DIR) clean >/dev/null || true
	if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR) clean >/dev/null || true; fi
	$(RMDIR) $(OBJ_DIR)
	@printf "$(GREEN)✔ Nettoyage terminé$(RESET)\n"

fclean: clean
	@printf "$(RED)🗑️  Suppression de $(NAME)...$(RESET)\n"
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean >/dev/null || true
	@printf "$(GREEN)✔ Nettoyage complet terminé$(RESET)\n"

re:
	@printf "$(YELLOW)🔄 Recompilation complète...$(RESET)\n"
	$(MAKE) fclean
	$(MAKE) all

-include $(DEPS)

.PHONY: all clean fclean re