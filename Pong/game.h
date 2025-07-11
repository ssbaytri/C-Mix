#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>

#define MAX 100

typedef struct paddle {
    int width;
    int height;
    int pos_x;
    int pos_y;
} paddle;

typedef struct ball {
    int x;
    int y;
    int dx;
    int dy;
    int width;
    int height;
} ball;

typedef struct player {
    char *name;
    int point;
} player;

// Function prototypes
int colors();
void draw_player_pad(paddle pad);
void draw_AIpad(paddle AIpad);
void draw_edges(int screenWidth, int screenHeight);
void move_ball(ball *ball);
void draw_ball(ball *ball);
int collision(paddle *pad, paddle *AIpad, ball *ball, int screenH, int screenW, player *p1, player *p2);
void score(int screenH, int screenW, player *p1, player *p2);
void get_input(paddle *pad, paddle *AIpad, ball *ball, int *game_over);
void game_loop();
void display_game_over(int screenH, int screenW, player *p1, player *p2);

#endif