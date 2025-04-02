#include "../include/snake.h"
#include <stdlib.h>

int main() {
    GameState game;
    
    init_game(&game);
    
    while (game.is_running) {
        handle_events(&game);
        
        if (game.skip) {
            game.skip = false;
            continue;
        }
        
        update_game(&game);
        draw_game(&game);
    }
    
    quit_game(&game);
    return 0;
}