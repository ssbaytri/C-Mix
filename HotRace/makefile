NAME=hotrace

CC=cc
CFLAGS=-Wall -Wextra -Werror

SRCS = another.c
OBJS = $(SRCS:.c=.o)

HEADER = hotrace.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re