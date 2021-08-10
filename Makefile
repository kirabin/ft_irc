NAME	=	a.out
COMPILER=	clang++
FLAGS	=	-Wall -Wextra
SRC		=	mdenys_part/lib/*/*.cpp  mdenys_part/lib/*/*.hpp mdenys_part/main.cpp
INC		=	mdenys_part/include_files
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
