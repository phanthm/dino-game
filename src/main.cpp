#include "raylib.h"
#include "raymath.h"

const int tile_size = 50;
const int x_tiles = 24;
const int y_tiles = 14;
const int screen_width = tile_size * x_tiles;
const int screen_height = tile_size * y_tiles;

const int GROUND = 12;

class Dino {
private:
int x, y;
int width, height;
Color color = BLACK;

public:
Dino(int x, int y, int width, int height) {
    this->x = x * tile_size;
    this->y = y * tile_size;
    this->width = width;
    this->height = height;
}

void Draw() {
    DrawRectangle(x, y, width, height, color);
}

};

int main(void) {

    Dino dino(0, 0, tile_size, tile_size);

    InitWindow(screen_width, screen_height, "Dino Game!");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        dino.Draw();
        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
