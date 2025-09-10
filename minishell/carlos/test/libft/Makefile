# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/30 11:11:20 by cade-jes          #+#    #+#              #
#    Updated: 2025/08/14 16:26:47 by cade-jes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =	real_ft/ft_atoi.c \
		real_ft/ft_atoll.c \
		real_ft/ft_bzero.c \
		real_ft/ft_calloc.c \
		real_ft/ft_realloc.c \
		real_ft/ft_isalnum.c \
		real_ft/ft_isalpha.c \
    	real_ft/ft_isascii.c \
		real_ft/ft_isdigit.c \
		real_ft/ft_isprint.c \
		real_ft/ft_memchr.c \
		real_ft/ft_memcmp.c \
    	real_ft/ft_memcpy.c \
		real_ft/ft_memmove.c \
		real_ft/ft_memset.c \
		real_ft/ft_strchr.c \
		real_ft/ft_strdup.c \
    	real_ft/ft_strlcat.c \
		real_ft/ft_strcpy.c \
		real_ft/ft_strlcpy.c \
		real_ft/ft_strlen.c \
		real_ft/ft_strcmp.c \
		real_ft/ft_strncmp.c \
		real_ft/ft_strnstr.c \
    	real_ft/ft_strrchr.c \
		real_ft/ft_tolower.c \
		real_ft/ft_toupper.c \
		review_ft/ft_substr.c \
		review_ft/ft_strjoin.c \
    	review_ft/ft_strtrim.c \
		review_ft/ft_split.c \
		review_ft/ft_itoa.c \
		review_ft/ft_strmapi.c \
		review_ft/ft_striteri.c \
    	review_ft/ft_putchar_fd.c \
		review_ft/ft_putstr_fd.c \
		review_ft/ft_putendl_fd.c \
		review_ft/ft_putnbr_fd.c \
		printf/ft_printf.c	\
		printf/ft_print_args.c	\
		printf/ft_print_adress.c \
		printf/ft_print_hex.c \
		list/ft_lstadd_back.c \
		list/ft_lstclear.c \
		list/ft_lstiter.c \
		list/ft_lstlast.c \
		list/ft_lstmap.c \
        list/ft_lstnew.c \
		list/ft_lstsize.c \
		list/ft_lstdelone.c \
		list/ft_lstadd_front.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		creation_ft/free_2.c

OBJ_DIR		=	obj
OBJS		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
DEP			=	$(SRCS:%.c=$(OBJ_DIR)/%.d)

CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror -g3 -MMD -MP
RM 				= rm -rf

all: $(NAME)

$(OBJ_DIR)/%.o:	%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME):	$(OBJ_DIR) $(OBJS)
				ar -rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJ_DIR)

fclean: clean
				$(RM) $(NAME)

re: 	fclean all

.PHONY: all clean fclean re

-include $(DEP)