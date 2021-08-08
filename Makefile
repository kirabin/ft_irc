NAME	=	a.out
COMPILER=	clang++
FLAGS	=	-Wall -Wextra -Werror
SRC		=	source_files
INC		=	include_files
OBJ		=	$(SRC:.cpp=.o)

all: $(NAME)

%.o: %.cpp $(INC)
	$(COMPILER) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(COMPILER) $(FLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f */*.o
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

start_bircd:
	make -C bircd/
	
