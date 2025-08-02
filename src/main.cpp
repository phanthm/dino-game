#include "raylib.h"

int main(void) {
    const int screenWidth = 1920 * 0.75;
    const int screenHeight = 1080 * 0.75;

    InitWindow(screenWidth, screenHeight, "Dino Game!");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("DINO GAME", 190, 200, 80, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
