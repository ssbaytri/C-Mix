all:
	gcc -o game game.c -lraylib -lm -lpthread -ldl -lrt -lX11

clean:
	rm -f game

run: all
	./game

.PHONY: all clean