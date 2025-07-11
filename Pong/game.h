#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct paddle
{
	int width;
	int height;
	int pos_x;
	int pos_y;
	int dx;
	int dy;
}				paddle;

typedef struct ball
{
	int ball_x;
	int ball_y;
	int dx;
	int dy;
	int ball_h;
}				ball;

typedef struct player
{
	char *name;
	int point;
}				player;

#endif
