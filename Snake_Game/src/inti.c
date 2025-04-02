#include "../include/init.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

void init_game(GameState *game) {
    srand(time(NULL));
    
    // Initialize game state
    game->head.x = 0;
    game->head.y = 0;
    game->dir.x = 1;
    game->dir.y = 0;
    game->score = 0;
    game->skip = false;
    game->is_running = true;
    game->sw = 25;
    game->sh = 20;
    
    // Initialize ncurses
    game->win = initscr();
    keypad(game->win, true);
    noecho();
    nodelay(game->win, true);
    curs_set(0);
    
    if (has_colors() == FALSE) {
        endwin();
        fprintf(stderr, "Your terminal does not support color\n");
        exit(1);
    }
    
    // Initialize colors
    start_color();
    use_default_colors();
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_YELLOW, -1);
    
    // Initialize food
    game->food.x = rand() % game->sw;
    game->food.y = rand() % game->sh;
    
    sprintf(game->score_text, "[ Score: %d ]", game->score);
}

void restart_game(GameState *game) {
    game->head.x = 0;
    game->head.y = 0;
    game->dir.x = 1;
    game->dir.y = 0;
    game->score = 0;
    sprintf(game->score_text, "[ Score: %d ]", game->score);
    game->is_running = true;
}

void quit_game() {
    endwin();
    printf("\e[1;1H\e[2J");
    printf("\e[?25h");
    exit(0);
}