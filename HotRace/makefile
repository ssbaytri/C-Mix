NAME=hotrace

CC=cc
CFLAGS=-Wall -Wextra -Werror

SRCS = hotrace.c utils.c utils2.c utils3.c 
OBJS = $(SRCS:.c=.o)

HEADER = hotrace.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re