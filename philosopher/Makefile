# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/25 10:09:54 by clfouger          #+#    #+#              #
#    Updated: 2025/08/26 14:09:15 by clfouger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   PHILO                                      #
# **************************************************************************** #

NAME        = philo

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread

SRCS        = main.c parsing.c routine.c utils.c clean.c
OBJS        = $(SRCS:.c=.o)

INCS        = philo.h

# Règle principale
all: $(NAME)

$(NAME): $(OBJS) $(INCS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compilation des .c en .o
%.o: %.c $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	rm -f $(OBJS)

# Nettoyage complet
fclean: clean
	rm -f $(NAME)

# Recompile tout
re: fclean all

.PHONY: all clean fclean re
