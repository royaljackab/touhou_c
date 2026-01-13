#include "test_task.h"
#include "main.h"
#include "menu.h"
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

    gameState gameState = TITLE_SCREEN;
    
    void* moonlightState = NULL;

    while(!WindowShouldClose()) {
        switch(gameState){
            case TITLE_SCREEN:
                menu_task(&gameState);
            break;
            case MOONLIGHT:
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
            break;
        }
    }

    AssetsUnload();
    CloseWindow();
}