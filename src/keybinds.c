#include "../lib/keybinds.h"
#include "../lib/globals.h"
#include "../lib/button.h"
#include "../lib/settings.h"
#include "../lib/game_state.h"
#include <stdio.h>

//fonctions state 

enum {
    DONE,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_DOWN,
    MOVE_UP,
    SHOOT,
    FOCUS_MODE,
    VALIDATE,
    PAUSE,
    BOMB,
    SKIP,
    SAVE
};

void state_menu_keybinds_draw(GameContext *ctx){
    ClearBackground(BLACK);

    DrawText("CONTROLS", 50, 200, 80, RED);
    draw_text(&ctx->button);
    draw_cursor(&ctx->button);
}

void state_menu_keybinds_update(GameContext *ctx){
    button_update(&ctx->button,&ctx->input);
    if(button_is_validated(&ctx->button)){
        switch(ctx->button.selection){
            case DONE:
                ctx->nextStateID = STATE_MENU_TITLE;
                break;
            case MOVE_LEFT:
                button_get_key("move_left", &ctx->input.keybinds.left);
                break;
            case MOVE_RIGHT:
                button_get_key("move_right", &ctx->input.keybinds.right);
                break;
            case MOVE_DOWN:
                button_get_key("move_down", &ctx->input.keybinds.down);
                break;
            case MOVE_UP:
                button_get_key("move_up", &ctx->input.keybinds.up);
                break;
            case SHOOT:
                button_get_key("shoot", &ctx->input.keybinds.shoot);
                break;
            case FOCUS_MODE:
                button_get_key("focus_mode", &ctx->input.keybinds.focus);
                break;
            case VALIDATE:
                button_get_key("validate", &ctx->input.keybinds.validate);
                break;
            case PAUSE:
                button_get_key("pause", &ctx->input.keybinds.pause);
                break;
            case BOMB:
                button_get_key("bomb", &ctx->input.keybinds.bomb);
                break;
            case SAVE:
                saveSettings(ctx);
                break;
        }
    }
}


void state_menu_keybinds_init(GameContext *ctx){
    ctx->button = button_system_init();
    button_create_text(&ctx->button, 50, 400, "DONE", 40, WHITE);

    button_create_text(&ctx->button, 60, 450, "move_left", 20, WHITE);
    button_create_text(&ctx->button, 60, 470, "move_right", 20, WHITE);
    button_create_text(&ctx->button, 60, 490, "move_down", 20, WHITE);
    button_create_text(&ctx->button, 60, 510, "move_up", 20, WHITE);
    button_create_text(&ctx->button, 60, 530, "shoot", 20, WHITE);
    button_create_text(&ctx->button, 60, 550, "focus_mode", 20, WHITE);
    button_create_text(&ctx->button, 60, 570, "validate", 20, WHITE);
    button_create_text(&ctx->button, 60, 590, "pause", 20, WHITE);
    button_create_text(&ctx->button, 60, 610, "bomb", 20, WHITE);
    button_create_text(&ctx->button, 60, 630,"skip",20 ,WHITE);

    button_create_text(&ctx->button, 250, 400, "SAVE", 40, WHITE);
}

GameState state_menu_keybinds = {
    .init = state_menu_keybinds_init,
    .update = state_menu_keybinds_update,
    .draw = state_menu_keybinds_draw,
    .cleanup = NULL
};

//Fonctions de boutons
void button_get_key(const char* target_name, KeyboardKey* key_target) {
    Rectangle rec = {100, 400, PANEL_WIDTH - 200, 200};
    int key_assigned = 0;
    KeyboardKey pressedKey = KEY_NULL;
    
    while (GetKeyPressed() != 0) { }
    
    while (!WindowShouldClose() && !key_assigned) {
        pressedKey = GetKeyPressed();
        if (pressedKey != KEY_NULL && pressedKey != KEY_ESCAPE) {
            input_change_keybind(key_target, pressedKey);
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
