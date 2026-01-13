#include "menu.h"
#include <stdio.h>

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

void menu(gameState *gameState){
    static int selection = 0;
    updateMenu(gameState, &selection);
    
    BeginDrawing();
        ClearBackground(BLACK);

        drawMenu(selection);
    EndDrawing(); 
}