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


GREEN ='\033[1;32m'
ORANGE ='\033[1;33m'
NC='\033[0m'

.PHONY: bircd

all: assembling $(NAME) assembled

%.o: %.cpp $(INC)
	$(COMPILER) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	@$(COMPILER) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@rm -f */*.out
	@rm -f *.out
	@rm -f */*.gch
	@rm -f *.gch
	@rm -rf *.dSYM
	@rm -rf */*.dSYM
	@echo ${ORANGE}"Cleared..."$(NC)

fclean: clean
	@rm -f $(NAME)
	@echo ${ORANGE}"All cleared"$(NC)

re: fclean all

run:
	@echo $(GREEN)"Start!"$(NC)
	@./$(NAME) 127.0.0.1:6667:23

nc:
	@echo $(GREEN)"Enter to server new user"$(NC)
	@nc 127.0.0.1 6667

assembling:
	@echo $(ORANGE)"Assembling"$(NC)

assembled:
	@echo $(GREEN)"Assembled"$(NC)

irssi:
	irssi -c 127.0.0.1
