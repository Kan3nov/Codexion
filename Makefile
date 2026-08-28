SRC = src/main.c src/validation.c src/coders.c src/heap.c src/init.c src/mutex_access.c \
		src/main.c src/monitor.c

NAME = codxion

all: $(NAME)

$(NAME): $(SRC)
	@cc -Wextra -Werror -Wall $(SRC) -o ($NAME)
