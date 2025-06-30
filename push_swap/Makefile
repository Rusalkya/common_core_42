NAME = push_swap

SRCS_DIRS = . moves parsing
SRC_FILES =	main.c push_swap.c stack.c sort.c \
            radix.c push_little_swap.c \
            $(wildcard moves/*.c) \
            $(wildcard parsing/*.c)

OBJS = $(SRC_FILES:.c=.o)

CC			= cc -g
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

INCLUDES	= -I. -I$(LIBFT_DIR)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) -o $(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re