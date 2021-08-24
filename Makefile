NAME	=	a.out
COMPILER=	clang++
FLAGS	=	-Wall -Wextra -g
SRC		=	lib/Channel/Channel.cpp \
			lib/Invoker/Command.cpp \
			lib/Invoker/Commands/HelpCommand.cpp \
			lib/Invoker/Commands/JoinCommand.cpp \
			lib/Invoker/Commands/KickCommand.cpp \
			lib/Invoker/Commands/LeaveCommand.cpp \
			lib/Invoker/Commands/ListCommand.cpp \
			lib/Invoker/Commands/NameCommand.cpp \
			lib/Invoker/Commands/NickCommand.cpp \
			lib/Invoker/Commands/PassCommand.cpp \
			lib/Invoker/Commands/WhoCommand.cpp \
			lib/Invoker/Invoker.cpp \
			lib/Server/Server.cpp \
			lib/User/User.cpp \
			lib/Utils/utils.cpp \
			main.cpp
OBJ		=	$(SRC:.cpp=.o)
INC		=	lib/Channel/Channel.hpp \
			lib/Invoker/Command.hpp \
			lib/Invoker/Commands/HelpCommand.hpp \
			lib/Invoker/Commands/JoinCommand.hpp \
			lib/Invoker/Commands/KickCommand.hpp \
			lib/Invoker/Commands/LeaveCommand.hpp \
			lib/Invoker/Commands/ListCommand.hpp \
			lib/Invoker/Commands/NameCommand.hpp \
			lib/Invoker/Commands/NickCommand.hpp \
			lib/Invoker/Commands/PassCommand.hpp \
			lib/Invoker/Commands/WhoCommand.hpp \
			lib/Invoker/Invoker.hpp \
			lib/Server/Server.hpp \
			lib/User/User.hpp \
			lib/Utils/ircserv.hpp

.PHONY: bircd

all: $(NAME)

%.o: %.cpp $(INC)
	$(COMPILER) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(COMPILER) $(FLAGS) $(OBJ)

clean:
	rm -f */*.o
	rm -f *.o
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
	./a.out 127.0.0.1:6444:23

nc:
	nc 127.0.0.1 6444
