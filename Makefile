NAME	=	a.out
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
			src/Invoker/Invoker.cpp \
			src/Server/Server.cpp \
			src/User/User.cpp \
			src/Utils/utils.cpp \
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
			src/Invoker/Invoker.hpp \
			src/Server/Server.hpp \
			src/User/User.hpp \
			src/Utils/ircserv.hpp

.PHONY: bircd

all: $(NAME)

%.o: %.cpp $(INC)
	$(COMPILER) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(COMPILER) $(FLAGS) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -f */*.out
	rm -f *.out
	rm -f */*.gch
	rm -f *.gch
	rm -rf *.dSYM
	rm -rf */*.dSYM

fclean: clean
	rm -f $(NAME)

re: fclean all

bircd:
	make -C bircd/
	./bircd/bircd.out 6667

run:
	./a.out 127.0.0.1:6667:23

nc:
	nc 127.0.0.1 6667
