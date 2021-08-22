NAME	=	a.out
COMPILER=	clang++
FLAGS	=	-Wall -Wextra -g
SRC		=	source/lib/*/*.cpp source/lib/*/*.hpp source/main.cpp
INC		=	source/include_files

.PHONY: bircd

all: $(NAME)

$(NAME): $(SRC)
	$(COMPILER) $(FLAGS) $(SRC)

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
