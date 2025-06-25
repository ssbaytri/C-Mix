#include <raylib.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib example - keyboard input");
    SetTargetFPS(60);

    Vector2 ballPos = { (float)screenWidth / 2, (float)screenHeight / 2 };

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) ballPos.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) ballPos.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) ballPos.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) ballPos.y += 2.0f;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);
        DrawCircleV(ballPos, 50, MAROON);
        EndDrawing();
    }
    CloseWindow();
    return (0);
}