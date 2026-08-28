SRC = src/main.c src/validation.c src/coders.c src/heap.c src/init.c src/mutex_access.c \
		src/monitor.c src/heap_helper.c 

NAME = codxion

all: $(NAME)

$(NAME): $(SRC)
	@cc -Wextra -Werror -Wall $(SRC) -o $(NAME)
