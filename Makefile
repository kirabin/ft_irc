NAME	=	a.out
COMPILER=	clang++
FLAGS	=	-Wall -Wextra
SRC		=	src/lib/*/*.cpp  src/lib/*/*.hpp src/main.cpp
INC		=	src/include_files
# OBJ		=	$(SRC:.cpp=.o)

.PHONY: bircd

all: $(NAME)

$(NAME): $(SRC)
	$(COMPILER) $(FLAGS) $(SRC)

clean:
	rm -f */*.o
	rm -f *.o

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
