#include "raylib.h"

const int TILE_SIZE = 50;
const int X_TILES = 24;
const int Y_TILES = 14;
const int SCREEN_WIDTH = TILE_SIZE * X_TILES;
const int SCREEN_HEIGHT = TILE_SIZE * Y_TILES;

const int GRAVITY = 2000;
const int GROUND = TILE_SIZE * 11;
const int JUMP_VELOCITY = -700;
const int BASE_CACTUS_SPEED = -400;

int score = 0;

class Player {
private:
    Vector2 position;
    Vector2 velocity;
    int width, height;
    Color color;
    bool inJump;

public:
    Player() {
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

    Rectangle GetRect() {
        return {position.x, position.y, (float)width, (float)height};
    }

    void SetValuesToBase() {
        inJump = false;
    }


};

class Obstacle {
private:
    Vector2 position;
    Vector2 velocity;
    int width, height;
    Color color;

public:
    Obstacle() {
        position = {1.5 * SCREEN_WIDTH, GROUND - TILE_SIZE};
        velocity = {BASE_CACTUS_SPEED, 0};
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

        velocity.x -= 0.0005 * GetTime();

        if (position.x <= -TILE_SIZE) {
            position.x = SCREEN_WIDTH + GetRandomValue(1, X_TILES) * TILE_SIZE;
        }
    }

    Rectangle GetRect() {
        return {position.x, position.y, (float)width, (float)height};
    }

    void SetValuesToBase() {
        position = {1.5 * SCREEN_WIDTH, GROUND - TILE_SIZE};
        velocity = {BASE_CACTUS_SPEED, 0};
    }
};

int main(void) {

    Player player = Player();
    Obstacle obstacle = Obstacle();

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dino Game!");

    SetTargetFPS(60);

    bool gameOver = false;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (!gameOver) {
            player.Update(dt);
            obstacle.Update(dt);
            score += 1;

            if (CheckCollisionRecs(player.GetRect(), obstacle.GetRect())) {
                gameOver = true;
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        player.Draw();
        obstacle.Draw();

        if (gameOver) {
            DrawText("GAME OVER!", SCREEN_WIDTH / 2 - MeasureText("GAME OVER!", 80) / 2, SCREEN_HEIGHT / 2 - 80, 80, RED);
            DrawText("PRESS SPACE", SCREEN_WIDTH / 2 - MeasureText("PRESS SPACE", 40) / 2, SCREEN_HEIGHT / 2 , 40, RED);

            if (IsKeyPressed(KEY_SPACE)) {
                player.SetValuesToBase();
                obstacle.SetValuesToBase();
                score = 0;
                gameOver = false;
            }
        }

        DrawText(TextFormat("%i", score), TILE_SIZE, SCREEN_HEIGHT - TILE_SIZE - 30, 40, GRAY);

        DrawLine(0, GROUND, SCREEN_WIDTH, GROUND, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
