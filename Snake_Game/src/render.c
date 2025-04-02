#include "../include/render.h"

void draw_border(int y, int x, int w, int h) {
    mvaddch(y, x, ACS_ULCORNER);
    mvaddch(y, x + w * 2 + 1, ACS_URCORNER);
    
    for (int i = 1; i < w * 2 + 1; i++)
        mvaddch(y, x + i, ACS_HLINE);
    
    for (int i = 1; i < h + 1; i++) {
        mvaddch(y + i, x, ACS_VLINE);
        mvaddch(y + i, x + w * 2 + 1, ACS_VLINE);
    }
    
    mvaddch(y + h + 1, x, ACS_LLCORNER);
    mvaddch(y + h + 1, x + w * 2 + 1, ACS_LRCORNER);
    
    for (int i = 1; i < w * 2 + 1; i++)
        mvaddch(y + h + 1, x + i, ACS_HLINE);
}

void draw_game(GameState *game) {
    erase();
    
    // Draw food
    attron(COLOR_PAIR(1));
    mvaddch(game->food.y + 1, game->food.x * 2 + 1, '@');
    attroff(COLOR_PAIR(1));

    // Draw snake
    attron(COLOR_PAIR(2));
    for (int i = 0; i < game->score; i++)
        mvaddch(game->segments[i].y + 1, game->segments[i].x * 2 + 1, ACS_DIAMOND);
    mvaddch(game->head.y + 1, game->head.x * 2 + 1, 'O');
    attroff(COLOR_PAIR(2));
    
    // Draw border and score
    attron(COLOR_PAIR(3));
    draw_border(0, 0, game->sw, game->sh);
    attroff(COLOR_PAIR(3));
    
    mvaddstr(0, game->sw - 5, game->score_text);
}