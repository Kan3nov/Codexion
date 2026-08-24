NAME = main.c validation.c

all:
	@cc $(NAME) -o run -lpthread
