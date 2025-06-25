#include <raylib.h>

typedef enum GameScreen
{
    LOGO = 0,
    TITLE,
    GAMEPLAY,
    ENDING
} GameScreen;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib example - basic screen manager");
    GameScreen currScreen = LOGO;

    int frameCounter = 0;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        switch (currScreen)
        {
        case LOGO:
        {
            frameCounter++;
            if (frameCounter > 120)
                currScreen = TITLE;
        }
        break;
        case TITLE:
        {
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                currScreen = GAMEPLAY;
        }
        break;
        case GAMEPLAY:
        {
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                currScreen = ENDING;
        }
        break;
        case ENDING:
        {
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                currScreen = TITLE;
        }
        break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currScreen)
        {
        case LOGO:
        {
            DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
            DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);
        }
        break;
        case TITLE:
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
            DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
            DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
        }
        break;
        case GAMEPLAY:
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
            DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
            DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
        }
        break;
        case ENDING:
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
            DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
            DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
        }
        break;
        default:
            break;
        }
        EndDrawing();
    }
    CloseWindow();
    return (0);
}
