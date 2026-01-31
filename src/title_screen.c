#include "../lib/title_screen.h"
#include "../lib/globals.h"
#include "../lib/button.h"
#include "../lib/settings.h"
#include "../lib/game_state.h"
#include <stdio.h>


    // Button_Create_Text(50,400,"BEGIN GAME",40,WHITE, STATE_MENU_TITLE, STATE_MENU_TITLE,NO_BUTTON,NO_BUTTON,0,button_notImplemented);
    // Button_Create_Text(50,500,"MOONLIGHT TEST",40,WHITE, STATE_MENU_TITLE, STATE_TEST,NO_BUTTON,NO_BUTTON,1,NULL);
    // Button_Create_Text(50,600,"KEYBINDS",40,WHITE, STATE_MENU_TITLE, STATE_MENU_KEYBINDS,NO_BUTTON,NO_BUTTON,2,NULL);

    // Button_Create_Text(50,400,"DONE",40,WHITE, STATE_MENU_KEYBINDS, STATE_MENU_TITLE,NO_BUTTON,11,0,NULL);

    // Button_Create_Text(60,450,"move_left",20,WHITE, STATE_MENU_KEYBINDS, STATE_MENU_KEYBINDS, NO_BUTTON,9,1,button_getKey_left);
    // Button_Create_Text(60,470,"move_right",20,WHITE, STATE_MENU_KEYBINDS, STATE_MENU_KEYBINDS, NO_BUTTON,9,2,button_getKey_right);
    // Button_Create_Text(60,490,"move_down",20,WHITE, STATE_MENU_KEYBINDS, STATE_MENU_KEYBINDS, NO_BUTTON,9,3,button_getKey_down);
    // Button_Create_Text(60,510,"move_up",20,WHITE, STATE_MENU_KEYBINDS, STATE_MENU_KEYBINDS, NO_BUTTON,9,4,button_getKey_up);
    // Button_Create_Text(60,530,"shoot",20,WHITE, STATE_MENU_KEYBINDS, STATE_MENU_KEYBINDS, NO_BUTTON,9,5,button_getKey_shoot);
    // Button_Create_Text(60,550,"focus_mode",20,WHITE, STATE_MENU_KEYBINDS, STATE_MENU_KEYBINDS, NO_BUTTON,9,6,button_getKey_focus);
    // Button_Create_Text(60,570,"validate",20,WHITE, STATE_MENU_KEYBINDS, STATE_MENU_KEYBINDS, NO_BUTTON,9,7,button_getKey_validate);
    // Button_Create_Text(60,590,"pause",20,WHITE, STATE_MENU_KEYBINDS, STATE_MENU_KEYBINDS, NO_BUTTON,9,8,button_getKey_pause);
    // Button_Create_Text(60,610,"bomb",20,WHITE, STATE_MENU_KEYBINDS, STATE_MENU_KEYBINDS, NO_BUTTON,9,9,button_getKey_bomb);
    // Button_Create_Text(60,630,"skip",20,WHITE, STATE_MENU_KEYBINDS, STATE_MENU_KEYBINDS, NO_BUTTON,9,10,button_getKey_skip);

    // Button_Create_Text(250,400,"SAVE",40,WHITE, STATE_MENU_KEYBINDS, STATE_MENU_KEYBINDS, 0,NO_BUTTON,11,saveSettings);


//fonctions state 

enum {
    BEGIN_GAME,
    MOONLIGHT_TEST,
    KEYBINDS
};

void state_menu_title_draw(GameContext *ctx){
    ClearBackground(BLACK);

    DrawText("TOUHOU_C", 50, 200, 80, RED);
    draw_text(&ctx->button);
    draw_cursor(&ctx->button);
}

void state_menu_title_update(GameContext *ctx){
    button_update(&ctx->button,&ctx->input);
    if(button_is_validated(&ctx->button)){
        switch(ctx->button.selection){
            case BEGIN_GAME:
                button_notImplemented();
                break;
            case MOONLIGHT_TEST:
                ctx->nextStateID = STATE_TEST;
                break;
            case KEYBINDS:
                ctx->nextStateID = STATE_MENU_KEYBINDS;
                break;
        }
    }
}


void state_menu_title_init(GameContext *ctx){
    ctx->button=button_system_init();
    button_create_text(&ctx->button, 50, 400, "BEGIN GAME", 40, WHITE);
    button_create_text(&ctx->button, 50, 500, "MOONLIGHT TEST", 40, WHITE);
    button_create_text(&ctx->button, 50, 600, "KEYBINDS", 40, WHITE);
}

GameState state_menu_title = {
    .init = state_menu_title_init,
    .update = state_menu_title_update,
    .draw = state_menu_title_draw,
    .cleanup = NULL
};

//Fonctions de boutons
void button_notImplemented(){
    BeginDrawing();
        DrawText("NOT IMPLEMENTED", 400, 400, 40, RED);
    EndDrawing();
}
