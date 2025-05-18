CC = cc
CFLAGS = -Wall -Wextra -Werror  #-g -fsanitize=address
MLX_DIR = minilibx/
# MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

SRCS = src/main.c src/player.c

OBJS = $(SRCS:.c=.o)

NAME = raycasting

all: $(NAME)

%o : %c game.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

run: $(NAME)
	./$(NAME)

re:	fclean all