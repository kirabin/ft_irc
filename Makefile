NAME	=	ircserv
COMPILER=	clang++
FLAGS	=	-Wall -Wextra -g
SRC		=	src/Channel/Channel.cpp \
			src/Invoker/Command.cpp \
			src/Invoker/Commands/HelpCommand.cpp \
			src/Invoker/Commands/JoinCommand.cpp \
			src/Invoker/Commands/KickCommand.cpp \
			src/Invoker/Commands/LeaveCommand.cpp \
			src/Invoker/Commands/ListCommand.cpp \
			src/Invoker/Commands/UserCommand.cpp \
			src/Invoker/Commands/NickCommand.cpp \
			src/Invoker/Commands/PassCommand.cpp \
			src/Invoker/Commands/WhoCommand.cpp \
			src/Invoker/Commands/QuitCommand.cpp \
			src/Invoker/Commands/ErrorCommand.cpp \
			src/Invoker/Commands/NoticeCommand.cpp \
			src/Invoker/Commands/PrivateMessageCommand.cpp \
			src/Invoker/Invoker.cpp \
			src/Server/Server.cpp \
			src/User/User.cpp \
			main.cpp
OBJ		=	$(SRC:.cpp=.o)
INC		=	src/Channel/Channel.hpp \
			src/Invoker/Command.hpp \
			src/Invoker/Commands/HelpCommand.hpp \
			src/Invoker/Commands/JoinCommand.hpp \
			src/Invoker/Commands/KickCommand.hpp \
			src/Invoker/Commands/LeaveCommand.hpp \
			src/Invoker/Commands/ListCommand.hpp \
			src/Invoker/Commands/UserCommand.hpp \
			src/Invoker/Commands/NickCommand.hpp \
			src/Invoker/Commands/PassCommand.hpp \
			src/Invoker/Commands/WhoCommand.hpp \
			src/Invoker/Commands/QuitCommand.hpp \
			src/Invoker/Commands/ErrorCommand.hpp \
			src/Invoker/Commands/NoticeCommand.hpp \
			src/Invoker/Commands/PrivateMessageCommand.hpp \
			src/Invoker/Invoker.hpp \
			src/Server/Server.hpp \
			src/User/User.hpp \
			src/Utils/ircserv.hpp

<<<<<<< HEAD
GREEN ='\033[1;32m'
WHITE ='\033[0;37m'
YELLOW ='\033[1;33m'

.PHONY: bircd

=======
>>>>>>> dcc00eeb1760de9f617cbeaf299a90ea74cf54c7
all: $(NAME)

%.o: %.cpp $(INC)
	@$(COMPILER) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	@$(COMPILER) $(FLAGS) $(OBJ) -o $(NAME)
	@echo $(GREEN)"The project is assembled"

clean:
	@rm -f $(OBJ)
	@rm -f */*.out
	@rm -f *.out
	@rm -f */*.gch
	@rm -f *.gch
	@rm -rf *.dSYM
	@rm -rf */*.dSYM
	@echo ${YELLOW}"Cleared..."

fclean: clean
	@rm -f $(NAME)
	@echo ${YELLOW}"All cleared"

re: fclean all

run:
	@echo $(GREEN)"Start!"${WHITE}
	@./$(NAME) 127.0.0.1:6667:23

nc:
	@echo $(GREEN)"Enter to server new user"${WHITE}
	@nc 127.0.0.1 6667
