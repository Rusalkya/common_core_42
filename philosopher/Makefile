# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/25 10:09:54 by clfouger          #+#    #+#              #
#    Updated: 2025/09/01 13:43:13 by clfouger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = philo

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread

SRCS        = main.c parsing.c routine.c utils.c clean.c monitor.c
OBJS        = $(SRCS:.c=.o)

INCS        = philo.h

all: $(NAME)

$(NAME): $(OBJS) $(INCS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
