vpath %.c src
vpath %.h headers
vpath %.o objects

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

OBJS_DIR := $(foreach obj, $(OBJS), objects/$(obj))

HEADERS := codexion.h heap.h

NAME := codexion

all: objects $(NAME)

objects:
	@mkdir objects

$(NAME): $(OBJS)
	@cc -Wextra -Werror -Wall $(OBJS_DIR) -g -o $(NAME)

$(OBJS): %.o : %.c $(HEADERS)
	@cc -Wextra -Werror -Wall $< -g -c -o objects/$@

clean:
	@rm -rf objects

fclean: clean
	@rm -f $(NAME)

re: fclean all