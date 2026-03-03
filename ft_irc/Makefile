NAME		= ircserv
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -I./includes

SRCS		= srcs/server/main.cpp \
			  srcs/server/Server.cpp \
			  srcs/client/Client.cpp \
			  srcs/client/Channel.cpp \
			  srcs/parsing/Parser.cpp \
			  srcs/parsing/commands/Invite.cpp \
			  srcs/parsing/commands/Join.cpp \
			  srcs/parsing/commands/Kick.cpp \
			  srcs/parsing/commands/Mode.cpp \
			  srcs/parsing/commands/Nick.cpp \
			  srcs/parsing/commands/Pass.cpp \
			  srcs/parsing/commands/Privmsg.cpp \
			  srcs/parsing/commands/Quit.cpp \
			  srcs/parsing/commands/Topic.cpp \
			  srcs/parsing/commands/User.cpp \
			  srcs/parsing/commands/Part.cpp

OBJS		= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
