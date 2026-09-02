vpath %.c src
vpath %.h headers

SRCS = main.c \
	validation.c \
	coders.c \
	heap.c \
	init.c \
	mutex_access.c \
	monitor.c \
	heap_helper.c \
	utility.c

OBJS := $(SRCS:%.c=%.o)

HEADERS := codexion.h heap.h

NAME := codexion

all: $(NAME)

$(NAME): $(OBJS)
	cc -Wextra -Werror -Wall $(OBJS) -g -o $(NAME)

$(OBJS): %.o : src/%.c $(HEADERS)
	cc -Wextra -Werror -Wall $< -g -c

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all