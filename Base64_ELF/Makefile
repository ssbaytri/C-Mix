CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = base64

src = main.c
objs = $(src:.c=.o)

all: $(NAME)

$(NAME): $(objs)
	$(CC) $(CFLAGS) -o $(NAME) $(objs)

clean:
	rm -f $(objs)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re