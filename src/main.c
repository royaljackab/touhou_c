#include "test2.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test");
    SetTargetFPS(60);

    Load_BulletSprites();
    Load_PlayerSprites();
    Load_Players();
    InitPlayer(REIMU_A);
    AssetsLoad();
    Initialize();

    while(!WindowShouldClose()) {
        MainLoop();
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