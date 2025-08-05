#include "raylib.h"
#include "raymath.h"
#include "stdio.h"

const int TILE_SIZE = 50;
const int X_TILES = 24;
const int Y_TILES = 14;
const int SCREEN_WIDTH = TILE_SIZE * X_TILES;
const int SCREEN_HEIGHT = TILE_SIZE * Y_TILES;

const int GRAVITY = 10;
const int GROUND = TILE_SIZE * 11;
const int JUMP_VELOCITY = -6;

class Dino {
private:
    Vector2 position;
    Vector2 velocity;
    int width, height;
    Color color = BLACK;

public:
    Dino(Vector2 position, Vector2 velocity, int width, int height) {
        this->position = position;
        this->velocity = velocity;
        this->width = width;
        this->height = height;
    }

    void Draw() {
        DrawRectangle(position.x, position.y, width, height, color);
    }

    void Update(float dt) {
        position.x += velocity.x;
        position.y += velocity.y;

        if (position.y >= GROUND - height) {
            velocity.y = 0;
            position.y = GROUND - height;
        } else {
            velocity.y += GRAVITY * dt;
        }

        if (IsKeyPressed(KEY_SPACE)) {
            Jump();
        }
    }

    void Jump() {
        velocity.y = JUMP_VELOCITY;
        printf("space pressed");

    }


};

int main(void) {

    Dino dino = Dino({3 * TILE_SIZE, GROUND - TILE_SIZE}, {0, 0}, TILE_SIZE, TILE_SIZE);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dino Game!");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        dino.Update(dt);

        BeginDrawing();
        dino.Draw();
        DrawLine(0, GROUND, SCREEN_WIDTH, GROUND, BLACK);
        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
