#include "test_task.h"
#include <stddef.h>
#include <stdio.h>
#include "menu.h"

    varGlobals globals;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Night of nights");
    SetTargetFPS(60);

    Load_BulletSprites();
    Load_PlayerSprites();
    Load_Players();
    InitPlayer(REIMU_A);
    AssetsLoad();
    initialize();

    globals.gameState = TITLE_SCREEN;
    globals.pause = 0;
    
    void* moonlightState = NULL;

    while(!WindowShouldClose()) {
        switch(globals.gameState){
            case TITLE_SCREEN:
                menu();
            break;
            case MOONLIGHT:
                
                if(!globals.pause){
                    UpdateObjects();
                    moonlight_task(&moonlightState);
                    UpdatePlayer();
                    UpdateAnimations();
                    UpdateAnimationPlayer();
                    UpdateCollisions();
                }

                BeginDrawing();
                    ClearBackground(BLACK);
                    DrawObjects();
                    DrawPlayer();
                EndDrawing();
            break;
        }
        if(globals.gameState != TITLE_SCREEN){
            pauseGame();
        }
        if(globals.pause){
            pauseMenu();
        }
    }


    AssetsUnload();
    CloseWindow();
}