NAME	=	a.out
COMPILER=	clang++
FLAGS	=	-Wall -Wextra -g
SRC		=	main.cpp \
			lib/Channel/Channel.cpp \
			lib/Invoker/Command.cpp \
			lib/Invoker/HelpCommand.cpp \
			lib/Invoker/Invoker.cpp \
			lib/Invoker/JoinCommand.cpp \
			lib/Invoker/KickCommand.cpp \
			lib/Invoker/LeaveCommand.cpp \
			lib/Invoker/ListCommand.cpp \
			lib/Invoker/NickCommand.cpp \
			lib/Invoker/PassCommand.cpp \
			lib/Invoker/WhoCommand.cpp \
			lib/Server/Server.cpp \
			lib/User/User.cpp \
			lib/Utils/utils.cpp
OBJ		=	$(SRC:.cpp=.o)
INC		=


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
