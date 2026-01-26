#include "title_screen.h"
#include "globals.h"
#include "menu.h"
#include "settings.h"
#include <stdio.h>


//si le bouton n'effectue pas de traitement: mettre le dernier paramètre de Button_Create à NULL

void init_menu(){
    //main menu
    Button_Create_Text(50,400,"BEGIN GAME",40,WHITE,MAIN_MENU,MAIN_MENU,NO_BUTTON,NO_BUTTON,0,button_notImplemented);
    Button_Create_Text(50,500,"MOONLIGHT TEST",40,WHITE,MAIN_MENU,MAIN_MENU,NO_BUTTON,NO_BUTTON,1,button_moonlight);
    Button_Create_Text(50,600,"KEYBINDS",40,WHITE,MAIN_MENU,KEYBINDS,NO_BUTTON,NO_BUTTON,2,NULL);

    //keybinds
    Button_Create_Text(50,400,"DONE",40,WHITE,KEYBINDS,MAIN_MENU,NO_BUTTON,9,0,NULL);
    Button_Create_Text(250,400,"SAVE",40,WHITE,KEYBINDS,KEYBINDS,0,NO_BUTTON,9,saveSettings);

    Button_Create_Text(60,450,"move_left",20,WHITE,KEYBINDS,KEYBINDS,NO_BUTTON,9,1,button_getKey_move_left);
    Button_Create_Text(60,470,"move_right",20,WHITE,KEYBINDS,KEYBINDS,NO_BUTTON,9,2,button_getKey_move_right);
    Button_Create_Text(60,490,"move_down",20,WHITE,KEYBINDS,KEYBINDS,NO_BUTTON,9,3,button_getKey_move_down);
    Button_Create_Text(60,510,"move_up",20,WHITE,KEYBINDS,KEYBINDS,NO_BUTTON,9,4,button_getKey_move_up);
    Button_Create_Text(60,530,"shoot",20,WHITE,KEYBINDS,KEYBINDS,NO_BUTTON,9,5,button_getKey_shoot);
    Button_Create_Text(60,550,"focus_mode",20,WHITE,KEYBINDS,KEYBINDS,NO_BUTTON,9,6,button_getKey_focus_mode);
    Button_Create_Text(60,570,"validate",20,WHITE,KEYBINDS,KEYBINDS,NO_BUTTON,9,7,button_getKey_validate);
    Button_Create_Text(60,590,"pause",20,WHITE,KEYBINDS,KEYBINDS,NO_BUTTON,9,8,button_getKey_pause);
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

void button_getKey_(const char* target_name, KeyboardKey* key_target) {
    Rectangle rec = {100, 400, PANEL_WIDTH - 200, 200};
    int key_assigned = 0;
    KeyboardKey pressedKey = KEY_NULL;
    
    while (GetKeyPressed() != 0) { }
    
    while (!WindowShouldClose() && !key_assigned) {
        pressedKey = GetKeyPressed();
        if (pressedKey != KEY_NULL && pressedKey != KEY_ESCAPE) {
            *key_target = pressedKey;
            key_assigned = 1;
        }
        BeginDrawing();
            DrawRectangleRec(rec, BLACK);
            DrawRectangleLinesEx(rec, 3, WHITE);
            DrawText(TextFormat("Press the new key for '%s'", target_name), 120, 420, 20, WHITE);
            DrawText("(Press ESC to cancel)", 120, 460, 15, GRAY);
        EndDrawing();
    }
}

DECLARE_BUTTON_GET_KEY_FUNCTION(move_left)
DECLARE_BUTTON_GET_KEY_FUNCTION(move_right)
DECLARE_BUTTON_GET_KEY_FUNCTION(move_up)
DECLARE_BUTTON_GET_KEY_FUNCTION(move_down)
DECLARE_BUTTON_GET_KEY_FUNCTION(shoot)
DECLARE_BUTTON_GET_KEY_FUNCTION(pause)
DECLARE_BUTTON_GET_KEY_FUNCTION(validate)
DECLARE_BUTTON_GET_KEY_FUNCTION(focus_mode)
