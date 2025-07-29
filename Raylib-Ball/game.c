#include <raylib.h>

int main(void)
{
    int width, height;
    width = 800;
    height = 600;

    float ball_size = 40.0f;
    int ball_vel = 4;
    int ball_x = width / 2;
    int ball_y = height / 2;
    int gravity = 3;

    InitWindow(width, height, "Raylib-Ball");

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();

        int ball_bottom = ball_y + ball_size;
        if (ball_bottom >= height)
        {
            ball_vel = 0;
            ball_y = height - ball_size;
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            ball_vel = -30;
        }

        ball_y += ball_vel;
        ball_vel += gravity;
        
        ClearBackground(RAYWHITE);
        DrawCircle(ball_x, ball_y, ball_size, RED);

        EndDrawing();
    }
    return 0;
}