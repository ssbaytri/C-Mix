#ifndef SNAKE_H
#define SNAKE_H

#include <curses.h>
#include <stdbool.h>

#define MAX_SCORE 256
#define FRAME_TIME 111000

typedef struct {
    int x;
    int y;
} Vec2;

// Game state
typedef struct {
    Vec2 head;
    Vec2 dir;
    Vec2 segments[MAX_SCORE + 1];
    Vec2 food;
    int score;
    char score_text[16];
    bool skip;
    bool is_running;
    int sw;
    int sh;
    WINDOW *win;
} GameState;

// Include all component headers
#include "init.h"
#include "input.h"
#include "collision.h"
#include "render.h"
#include "game_logic.h"

#endif // SNAKE_H