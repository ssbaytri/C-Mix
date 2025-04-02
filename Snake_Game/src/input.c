#include "../include/input.h"
#include "../include/init.h"

void handle_events(GameState *game) {
    int pressed = wgetch(game->win);
    
    switch (pressed) {
        case KEY_LEFT:
            if (game->dir.x == 1) {
                game->skip = true;
                return;
            }
            game->dir.x = -1;
            game->dir.y = 0;
            break;
            
        case KEY_RIGHT:
            if (game->dir.x == -1) {
                game->skip = true;
                return;
            }
            game->dir.x = 1;
            game->dir.y = 0;
            break;
            
        case KEY_UP:
            if (game->dir.y == 1) {
                game->skip = true;
                return;
            }
            game->dir.x = 0;
            game->dir.y = -1;
            break;
            
        case KEY_DOWN:
            if (game->dir.y == -1) {
                game->skip = true;
                return;
            }
            game->dir.x = 0;
            game->dir.y = 1;
            break;
            
        case ' ':
            if (!game->is_running)
                restart_game(game);
            break;
            
        case '\e':
            game->is_running = false;
            quit_game(game);
            break;
    }
}