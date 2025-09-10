# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/13 15:31:24 by cade-jes          #+#    #+#              #
#    Updated: 2025/08/23 13:46:19 by cade-jes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	pwd/ft_pwd.c \
		error/ft_error.c \
		echo/ft_echo.c \
		cd/ft_cd.c \
		ft_utils/ft_utils_1.c

OBJ_DIR		=	obj
OBJS		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
DEP			=	$(SRCS:%.c=$(OBJ_DIR)/%.d)

CC			=	cc
RM			=	rm -rf
CFLAGS		=	-Wall -Wextra -Werror -g3 -MMD -MP

LIBFT		=	./libft
LIBFT_A		=	$(LIBFT)/libft.a

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	
$(OBJ_DIR)/%.o:	%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A):
	make -C $(LIBFT) all
	
$(NAME): $(OBJ_DIR) $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)

clean:
	make -C $(LIBFT) fclean
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)