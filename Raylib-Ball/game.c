#include "game.h"

bool ball_on_platform(Ball ball, Platform platforms[], int count)
{
    for (int i = 0; i < count; i++)
    {
        Platform platform = platforms[i];
        Rectangle platfrom_rec = {
            .x = platform.x,
            .y = platform.y,
            .width = platform.width,
            .height = platform.height
        };
        Vector2 ball_pos = { .x = ball.x, .y = ball.y };
        int ball_bottom = ball.y + ball.size;
        if (CheckCollisionCircleRec(ball_pos, ball.size, platfrom_rec))
        {
            return true;
        }
    }
    return false;
}

bool ball_on_ground(int pos_y, int win_height, float ball_size)
{
    if (pos_y >= win_height - ball_size)
        return true;
    return false;
}

int main(void)
{
    int width, height;

    width = 800;
    height = 600;

    Ball ball = { .x = width / 2, .y = height / 2, .size = 40.0f, .vel = 4};
    int gravity = 3;

    Platform platforms[3] = {
    { .x = 0, .y = height - 20, .width = width, .height = 20 },
    { .x = 150, .y = 500, .width = 200, .height = 20 },
    { .x = 500, .y = 300, .width = 180, .height = 20 }
}   ;

    InitWindow(width, height, "Raylib-Ball");

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();

        if (ball_on_platform(ball, platforms, 3))
        {
            ball.vel = 0;
            // ball.y = height - ball.size;
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            ball.vel = -30;
        }

        if (IsKeyDown(KEY_LEFT))
            ball.x -= 4;

        if (IsKeyDown(KEY_RIGHT))
            ball.x += 4;

        ball.y += ball.vel;
        ball.vel += gravity;

        ClearBackground(RAYWHITE);

        for (int i = 0; i < 3; i++) {
            DrawRectangle(platforms[i].x, platforms[i].y,
                  platforms[i].width, platforms[i].height, BLACK);
        }


        DrawCircle(ball.x, ball.y, ball.size, RED);

        EndDrawing();
    }
    return 0;
}