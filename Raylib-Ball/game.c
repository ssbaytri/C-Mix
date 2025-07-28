#include <raylib.h>

int main(void)
{
    int width, height;
    width = 800;
    height = 600;

    float ball_size = 40.0f;

    InitWindow(width, height, "Raylib-Ball");

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawCircle(width / 2, height / 2, ball_size, RED);

        EndDrawing();
    }
    return 0;
}