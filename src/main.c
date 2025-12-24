#include "moonlight.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test");
    SetTargetFPS(60);

    Load_BulletSprites();
    Load_PlayerSprites();
    Load_Players();
    InitPlayer(REIMU_A);
    AssetsLoad();
    moonlight_init();

    while(!WindowShouldClose()) {
        moonlight();
        UpdateObjects();

        BeginDrawing();
            ClearBackground(BLACK);

            DrawObjects();
            DrawPlayer();
            UpdatePlayer();
            UpdateAnimations();
            UpdateAnimationPlayer();
            UpdateCollisions();
        EndDrawing();
    }

    AssetsUnload();
    CloseWindow();
}