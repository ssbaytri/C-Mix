#include "../include/game_logic.h"
#include "../include/collision.h"
#include "../include/input.h"
#include "../include/render.h"
#include <stdio.h>
#include <unistd.h>

void update_game(GameState *game) {
    // Update snake segments
    for (int i = game->score; i > 0; i--)
        game->segments[i] = game->segments[i - 1];
    game->segments[0] = game->head;

    // Move head
    game->head.x += game->dir.x;
    game->head.y += game->dir.y;

    // Check collisions
    if (collide_self(game, game->head) || 
        game->head.x < 0 || game->head.x >= game->sw || 
        game->head.y < 0 || game->head.y >= game->sh) {
        game->is_running = false;
        game_over(game);
    }
    
    // Check food collision
    if (collide(game->head, game->food)) {
        if (game->score < MAX_SCORE) {
            game->score++;
            sprintf(game->score_text, "[ Score: %d ]", game->score);
        } else {
            printf("You Win!\n");
        }
        game->food = reset_food(game);
    }
    
    usleep(FRAME_TIME);
}

void game_over(GameState *game) {
    while (game->is_running == false) {
        handle_events(game);
        mvaddstr(game->sh / 2, game->sw - 16, "              Game Over          ");
        mvaddstr(game->sh / 2 + 1, game->sw - 16, "[SPACE] to restart, [ESC] to quit ");
        attron(COLOR_PAIR(3));
        draw_border(game->sh / 2 - 1, game->sw - 17, 17, 2);
        attroff(COLOR_PAIR(3));
        usleep(FRAME_TIME);
    }
}