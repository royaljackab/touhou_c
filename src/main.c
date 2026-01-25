#include "test_task.h"
#include <stddef.h>
#include <stdio.h>
#include "menu.h"
#include "title_screen.h"

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

    init_menu();

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
                    DrawRectangleLines(PANEL_LEFT,PANEL_UP,PANEL_WIDTH,PANEL_HEIGHT,WHITE);
                    
                    DrawObjects();
                    DrawPlayer();
                    DrawRectangle(0,0,PANEL_LEFT,SCREEN_HEIGHT,BLACK);
                    DrawRectangle(PANEL_LEFT,0,SCREEN_WIDTH-PANEL_LEFT,PANEL_UP,BLACK);
                    DrawRectangle(PANEL_LEFT+PANEL_WIDTH,PANEL_UP,SCREEN_WIDTH-PANEL_LEFT-PANEL_WIDTH,SCREEN_HEIGHT-PANEL_UP,BLACK);
                    DrawRectangle(PANEL_LEFT,PANEL_UP+PANEL_HEIGHT,SCREEN_WIDTH-PANEL_WIDTH,SCREEN_HEIGHT-PANEL_HEIGHT-PANEL_UP,BLACK);
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