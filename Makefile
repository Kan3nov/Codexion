SRC1 = src/main.c
SRC2 = src/validation.c
SRC3 = src/coders.c
SRC4 = src/heap.c
SRC5 = src/init.c
SRC6 = src/mutex_access.c
SRC7 = src/monitor.c
SRC8 = src/heap_helper.c
SRC9 = src/utility.c

OBJ1 = main.o
OBJ2 = validation.o
OBJ3 = coders.o
OBJ4 = heap.o 
OBJ5 = init.o
OBJ6 = mutex_access.o
OBJ7 = monitor.o
OBJ8 = heap_helper.o
OBJ9 = utility.o

HEADERS = headers/codexion.h headers/heap.h

NAME = codexion

all: $(NAME)

$(NAME): $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5) $(OBJ6) $(OBJ7) $(OBJ8) $(OBJ9)
	cc -Wextra -Werror -Wall *.o -g -o $(NAME)

%.o : src/%.c $(HEADERS)
	cc -Wextra -Werror -Wall $< -g -c

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all