all:
	gcc -o game game.c -lraylib -lm -lpthread -ldl -lrt -lX11

clean:
	rm -f game

re: clean all

run: all
	./game

.PHONY: all clean