#include "../include/collision.h"
#include <stdlib.h>

bool collide(Vec2 a, Vec2 b) {
    return a.x == b.x && a.y == b.y;
}

bool collide_self(GameState *game, Vec2 pos) {
    for (int i = 0; i < game->score; i++) {
        if (collide(pos, game->segments[i]))
            return true;
    }
    return false;
}

Vec2 reset_food(GameState *game) {
    Vec2 new_food = {1 + rand() % (game->sw - 2), 1 + rand() % (game->sh - 2)};
    
    while (collide(game->head, new_food) || collide_self(game, new_food)) {
        new_food.x = 1 + rand() % (game->sw - 2);
        new_food.y = 1 + rand() % (game->sh - 2);
    }
    
    return new_food;
}