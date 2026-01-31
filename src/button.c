#include "../lib/button.h"
#include <stdio.h>
#include "../lib/game_state.h"
#include "../lib/input.h"
#include <string.h>


ButtonSystem button_system_init(){
    ButtonSystem buttonSystem;
    buttonSystem.nbButtons = 0;
    buttonSystem.selection = 0;
    return buttonSystem;
}

void button_create(ButtonSystem *buttonSystem, int x, int y){
    button_create_ex(buttonSystem, x, y, NO_BUTTON, NO_BUTTON);
}

void button_create_ex(ButtonSystem *buttonSystem, int x, int y, int left, int right){
    buttonSystem->buttons[buttonSystem->nbButtons].buttonLeft = left;
    buttonSystem->buttons[buttonSystem->nbButtons].buttonRight = right;
    buttonSystem->buttons[buttonSystem->nbButtons].validated = 0;
    buttonSystem->buttons[buttonSystem->nbButtons].pos.x = x;
    buttonSystem->buttons[buttonSystem->nbButtons].pos.y = y;

    buttonSystem->buttons[buttonSystem->nbButtons].text = NULL;
    buttonSystem->nbButtons++;
}

void button_create_text(ButtonSystem *buttonSystem, int x, int y, char * text, int size, Color color){
    button_create_text_ex(buttonSystem, x, y, text, size, color, NO_BUTTON, NO_BUTTON);
}

void button_create_text_ex(ButtonSystem *buttonSystem, int x, int y, char * text, int size, Color color, int left, int right){
    buttonSystem->buttons[buttonSystem->nbButtons].buttonLeft = left;
    buttonSystem->buttons[buttonSystem->nbButtons].buttonRight = right;
    buttonSystem->buttons[buttonSystem->nbButtons].validated = 0;
    buttonSystem->buttons[buttonSystem->nbButtons].pos.x = x;
    buttonSystem->buttons[buttonSystem->nbButtons].pos.y = y;
    
    buttonSystem->buttons[buttonSystem->nbButtons].text = text;
    buttonSystem->buttons[buttonSystem->nbButtons].size = size;
    buttonSystem->buttons[buttonSystem->nbButtons].color = color;

    buttonSystem->nbButtons++;
}

void button_update(ButtonSystem *buttonSystem, InputState *inputState){
    if(isPressed(inputState->down) && buttonSystem->selection < buttonSystem->nbButtons-1){
        (buttonSystem->selection)++;
    } 
    if(isPressed(inputState->up) && buttonSystem->selection > 0){
        (buttonSystem->selection)--;
    }
    if(isPressed(inputState->left)){
        if(buttonSystem->buttons[buttonSystem->selection].buttonLeft != NO_BUTTON) {
            buttonSystem->selection=buttonSystem->buttons[buttonSystem->selection].buttonLeft;
        }
    }
    if(isPressed(inputState->right)){
        if(buttonSystem->buttons[buttonSystem->selection].buttonRight != NO_BUTTON) {
            buttonSystem->selection=buttonSystem->buttons[buttonSystem->selection].buttonRight;
        }
    }
    buttonSystem->buttons[buttonSystem->selection].validated = isPressed(inputState->validate);
}

int button_is_validated(ButtonSystem *buttonSystem){    
    return buttonSystem->buttons[buttonSystem->selection].validated;
}

void draw_text(ButtonSystem *buttonSystem){
    for(int i = 0; i < buttonSystem->nbButtons; i++){
        if(buttonSystem->buttons[i].text != NULL){
            DrawText(buttonSystem->buttons[i].text, buttonSystem->buttons[i].pos.x, buttonSystem->buttons[i].pos.y, buttonSystem->buttons[i].size, buttonSystem->buttons[i].color);
        }
    }
}

void draw_cursor(ButtonSystem *buttonSystem){
    DrawText("*", buttonSystem->buttons[buttonSystem->selection].pos.x - 30,
        buttonSystem->buttons[buttonSystem->selection].pos.y, 
        buttonSystem->buttons[buttonSystem->selection].text != NULL ? buttonSystem->buttons[buttonSystem->selection].size : 20,
        WHITE);
}