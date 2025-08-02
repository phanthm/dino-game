#include "raylib.h"
#include "raymath.h"

class Dino {
private:
int x, y;
int width, height;
Color color = BLACK;

public:
Dino(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Draw() {
    DrawRectangle(x, y, width, height, color);
}

};

int main(void) {
    const int screenWidth = 1920 * 0.75;
    const int screenHeight = 1080 * 0.75;

    Dino dino(10, 10, 10, 10);

    InitWindow(screenWidth, screenHeight, "Dino Game!");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        dino.Draw();
        ClearBackground(RAYWHITE);

        DrawText("DINO GAME", 190, 200, 80, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
