#ifndef GAME_H
#define GAME_H

#include "../minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define WIDTH 1280
#define HEIGHT 720

// for Linux
// #define W 119
// #define A 97
// #define S 115
// #define D 100
// #define ESC 65307

// for macOS
#define W 13
#define A 0
#define S 1
#define D 2
#define ESC 53

#define PI 3.14159265358979323846

typedef struct s_player
{
	float x;
	float y;

	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;
} t_player;

typedef struct s_game
{
	void *mlx;
	void *win;
	void *img;

	char *data;
	int bpp;
	int size_line;
	int endian;
	t_player player;
} t_game;


void	init_player(t_player *player);
int key_press(int keycode, t_player *player);
int key_release(int keycode, t_player *player);
void    move_player(t_player *player);


#endif
