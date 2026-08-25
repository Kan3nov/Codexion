NAME = src/main.c src/validation.c

all:
	@cc $(NAME) -o run -lpthread
