#ifndef COLLISION_H
#define COLLISION_H

#include "snake.h"

// Function declarations
bool collide(Vec2 a, Vec2 b);
bool collide_self(GameState *game, Vec2 pos);
Vec2 reset_food(GameState *game);

#endif // COLLISION_H