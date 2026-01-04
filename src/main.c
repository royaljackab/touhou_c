#include "test_task.h"
#include <stddef.h>

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test");
    SetTargetFPS(60);

    Load_BulletSprites();
    Load_PlayerSprites();
    Load_Players();
    InitPlayer(REIMU_A);
    AssetsLoad();
    initialize();

    void* moonlightState = NULL;

    while(!WindowShouldClose()) {
        moonlight_task(&moonlightState);
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