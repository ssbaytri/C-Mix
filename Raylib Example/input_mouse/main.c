#include <raylib.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib example - mouse input");
    SetTargetFPS(60);

    Vector2 ballPos = { -100.0f, -100.0f };
    Color ballCol = DARKBLUE;
    int isCursHidden = 0;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_H))
        {
            if (!isCursHidden)
            {
                HideCursor();
                isCursHidden = 1;
            }
            else
            {
                ShowCursor();
                isCursHidden = 0;
            }
        }

        ballPos = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) ballCol = MAROON;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) ballCol = LIME;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) ballCol = DARKBLUE;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_SIDE)) ballCol = PURPLE;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_EXTRA)) ballCol = YELLOW;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_FORWARD)) ballCol = ORANGE;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_BACK)) ballCol = BEIGE;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircleV(ballPos, 40, ballCol);

        DrawText("move ball with mouse and click mouse button to change color", 10, 10, 20, DARKGRAY);
        DrawText("Press 'H' to toggle cursor visibility", 10, 30, 20, DARKGRAY);

        if (isCursHidden)
            DrawText("CURSOR HIDDEN", 20, 60, 20, RED);
        else
            DrawText("CURSOR VISIBLE", 20, 60, 20, LIME);

        EndDrawing();
    }
    CloseWindow();
    return (0);
}