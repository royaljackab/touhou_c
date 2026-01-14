#include "menu.h"
#include <stdio.h>
#include "globals.h"

void drawMenu(int selection){
    DrawText("TOUHOU_C", 50, 200, 80, RED);
    DrawText("BEGIN GAME", 50, 400, 40, WHITE);
    DrawText("MOONLIGHT TEST", 50, 500, 40, WHITE);

    switch (selection){
            case 0: 
                DrawText("*", 20, 400, 40, WHITE);
                break;
            case 1:
                DrawText("*", 20, 500, 40, WHITE);
                break;
    }
}

void updateMenu(gameState *gameState, int* selection){
    if(IsKeyPressed(KEY_DOWN) && *selection < NB_BUTTONS){
        (*selection)++;
    } 
    if(IsKeyPressed(KEY_UP) && *selection > 0){
        (*selection)--;
    }

    if(IsKeyDown(KEY_SPACE)){
        switch (*selection){
            case 0: 
                BeginDrawing();
                    DrawText("NOT IMPLEMENTED", 400, 400, 40, RED);
                EndDrawing();
                break;
            case 1:
                *gameState = MOONLIGHT;
                break;
        }
    }
}

void menu(){
    static int selection = 0;
    updateMenu(&globals.gameState, &selection);
    
    BeginDrawing();
        ClearBackground(BLACK);

        drawMenu(selection);
    EndDrawing(); 
}

void pauseGame(){
    if(IsKeyPressed(KEY_P)){
        globals.pause = !globals.pause;
    }
}

void pauseMenu(){
    DrawText("PAUSE", 100, 300, 50, RED);
    DrawRectangleLines(50, 50, PANEL_WIDTH - 100, PANEL_HEIGHT - 100, WHITE);
}