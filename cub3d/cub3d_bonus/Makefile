# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/05 09:49:46 by clfouger          #+#    #+#              #
#    Updated: 2025/12/01 15:06:41 by cade-jes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D_bonus
CC			=	cc

MAKEFLAGS	+=	--no-print-directory
.SILENT:

GREEN		=	\033[0;32m
CYAN		=	\033[0;36m
YELLOW		=	\033[0;33m
RED			=	\033[0;31m
RESET		=	\033[0m
BOLD		=	\033[1m

SRCS		=	srcs_bonus/main.c \
				srcs_bonus/display/minimap.c \
				srcs_bonus/display/minimap_2.c \
				srcs_bonus/display/frame.c \
				srcs_bonus/display/raycasting.c \
				srcs_bonus/display/draw_wall.c \
				srcs_bonus/display/draw_wall_utils.c \
				srcs_bonus/other/exit.c \
				srcs_bonus/other/exit_helpers.c \
				srcs_bonus/other/list.c \
				srcs_bonus/other/list_2.c \
				srcs_bonus/other/list_3.c \
				srcs_bonus/other/msg.c \
				srcs_bonus/other/init.c \
				srcs_bonus/other/init_helpers_2.c \
				srcs_bonus/other/init_helpers_3.c \
				srcs_bonus/other/utils.c \
				srcs_bonus/other/wall_hole_anim.c \
				srcs_bonus/movement/movement.c \
				srcs_bonus/movement/movement_utils.c \
				srcs_bonus/movement/movement_utils_2.c \
				srcs_bonus/movement/mouse.c \
				srcs_bonus/parsing/images.c \
				srcs_bonus/parsing/colors.c \
				srcs_bonus/parsing/map_checking.c \
				srcs_bonus/parsing/map_checking_2.c \
				srcs_bonus/parsing/read_map.c \
				srcs_bonus/parsing/read_map_utils.c \
				srcs_bonus/parsing/map_parsing.c \
				srcs_bonus/parsing/textures_parsing.c \
				srcs_bonus/parsing/init_player.c \
				srcs_bonus/parsing/parsing.c \
				srcs_bonus/parsing/flood_fill.c \
				srcs_bonus/parsing/flood_fill_utils.c \
				srcs_bonus/hammer/hammer_init.c \
				srcs_bonus/hammer/hammer_render.c \
				srcs_bonus/hammer/hammer_collect.c \
				srcs_bonus/hammer/hammer_world_render.c \
				srcs_bonus/hammer/hammer_world_utils.c \
				srcs_bonus/hammer/mouse_click.c \
				srcs_bonus/hammer/pov_hammer_attack.c \
				srcs_bonus/pov/pov_init.c \
				srcs_bonus/pov/pov_init_helpers.c \
				srcs_bonus/pov/pov_free.c \
				srcs_bonus/pov/pov_render.c \
				srcs_bonus/pov/pov_render_utils.c \
				srcs_bonus/pov/pov_animation.c \
				srcs_bonus/screamer/screamer.c \
				srcs_bonus/screamer/screamer_helpers.c \
				srcs_bonus/screamer/screamer_helpers_2.c \
				srcs_bonus/screamer/final_screamer.c \
				srcs_bonus/sounds/sound.c \
				srcs_bonus/sounds/sound_helpers.c \
				srcs_bonus/sounds/sound_music.c \
				srcs_bonus/sounds/footstep.c

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