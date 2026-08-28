NAME = src/main.c src/validation.c src/coders.c src/heap.c src/init.c src/mutex_access.c \
		src/main.c src/monitor.c



all:
	@cc $(NAME) -o run -lpthread
