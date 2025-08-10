#include "raylib.h"
#include "raymath.h"
#include "stdio.h"

const int TILE_SIZE = 50;
const int X_TILES = 24;
const int Y_TILES = 14;
const int SCREEN_WIDTH = TILE_SIZE * X_TILES;
const int SCREEN_HEIGHT = TILE_SIZE * Y_TILES;

const int GRAVITY = 1200;
const int GROUND = TILE_SIZE * 11;
const int JUMP_VELOCITY = -600;
const int CACTUS_SPEED = -600;

class Dino {
private:
    Vector2 position;
    Vector2 velocity;
    int width, height;
    Color color;
    bool inJump;

public:
    Dino() {
        position = {3 * TILE_SIZE, GROUND - TILE_SIZE};
        velocity = {0, 0};
        width = TILE_SIZE;
        height = TILE_SIZE;
        inJump = false;
        color = BLACK;
    }

    void Draw() {
        DrawRectangle(position.x, position.y, width, height, color);
    }

    void Update(float dt) {
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;

        if (position.y >= GROUND - height) {
            inJump = false;
            velocity.y = 0;
            position.y = GROUND - height;
        } else {
            velocity.y += GRAVITY * dt;
        }

        if (IsKeyPressed(KEY_SPACE) && !inJump) {
            Jump();
            inJump = true;
        }
    }

    void Jump() {
        velocity.y = JUMP_VELOCITY;
    }


};

class Cactus {
private:
    Vector2 position;
    Vector2 velocity;
    int width, height;
    Color color;

public:
    Cactus() {
        position = {SCREEN_WIDTH + TILE_SIZE, GROUND - TILE_SIZE};
        velocity = {CACTUS_SPEED, 0};
        width = TILE_SIZE;
        height = TILE_SIZE;
        color = RED;
    }

    void Draw() {
        DrawRectangle(position.x, position.y, width, height, color);
    }

    void Update(float dt) {
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;

        if (position.x <= -TILE_SIZE) {
            position.x = SCREEN_WIDTH + TILE_SIZE;
        }
    }
};

int main(void) {

    Dino dino = Dino();
    Cactus cactus = Cactus();

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dino Game!");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        dino.Update(dt);
        cactus.Update(dt);

        BeginDrawing();
        dino.Draw();
        cactus.Draw();
        DrawLine(0, GROUND, SCREEN_WIDTH, GROUND, BLACK);
        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
