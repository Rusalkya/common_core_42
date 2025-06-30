# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/30 11:11:20 by clfouger          #+#    #+#              #
#    Updated: 2025/06/25 11:04:17 by clfouger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC =	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
    	ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_memchr.c \
		ft_memcmp.c \
    	ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_strchr.c \
		ft_strdup.c \
    	ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strnstr.c \
    	ft_strrchr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_substr.c \
		ft_strjoin.c \
    	ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
    	ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_printf/ft_printf.c \
		ft_printf/ft_printf_utils.c \
		ft_printf/ft_putnbr_unsigned_pf.c \
		ft_printf/ft_putnbr_signed_pf.c \
		ft_lstadd_back_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstadd_front_bonus.c
		
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
