CC = clang
CFLAGS = -Wall -Iinclude
# LDFLAGS = -Llib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

EXAMPLE ?= basic_window

SRC = $(EXAMPLE)/main.c
OUT = game

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

run: all
	./$(OUT)

clean:
	rm -rf $(OUT)
