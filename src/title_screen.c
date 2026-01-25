#include "title_screen.h"
#include "globals.h"
#include "menu.h"
#include <stdio.h>

Sprite no_sprite;

//si le bouton n'effectue pas de traitement: mettre le dernier paramètre de Button_Create à NULL

void init_menu(){
    Button_Create(no_sprite,50,400,"BEGIN GAME",40,WHITE,MAIN_MENU,MAIN_MENU,0,button_notImplemented);
    Button_Create(no_sprite,50,500,"MOONLIGHT TEST",40,WHITE,MAIN_MENU,MAIN_MENU,1,button_moonlight);
}

//Fonctions de boutons
void button_notImplemented(){
    BeginDrawing();
        DrawText("NOT IMPLEMENTED", 400, 400, 40, RED);
    EndDrawing();
}

void button_moonlight(){
    globals.gameState = MOONLIGHT;
}