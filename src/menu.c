#include "menu.h"
#include <stdio.h>
#include "globals.h"
#include <string.h>

static int selection = 0;
static pageMenu page = MAIN_MENU;
static int nbButtons = 0;
button buttons[MAX_BUTTONS];

void Button_Create_Sprite(Sprite sprite, int x, int y, pageMenu pageCurrent, pageMenu pageNext, int buttonLeft, int buttonRight, int order, void (*function)(void)){
    buttons[nbButtons].sprite = sprite;
    buttons[nbButtons].pos.x = x;
    buttons[nbButtons].pos.y = y;
    buttons[nbButtons].pageCurrent = pageCurrent;
    buttons[nbButtons].pageNext = pageNext;
    buttons[nbButtons].buttonLeft = buttonLeft;
    buttons[nbButtons].buttonRight = buttonRight;
    buttons[nbButtons].order = order;
    buttons[nbButtons].function = function;
    nbButtons++;
}

void Button_Create_Text(int x, int y, char * text, int textSize, Color color, pageMenu pageCurrent, pageMenu pageNext, int buttonLeft, int buttonRight, int order, void (*function)(void)){
    buttons[nbButtons].pos.x = x;
    buttons[nbButtons].pos.y = y;
    strcpy(buttons[nbButtons].text,text);
    buttons[nbButtons].textSize = textSize;
    buttons[nbButtons].textColor = color;
    buttons[nbButtons].pageCurrent = pageCurrent;
    buttons[nbButtons].pageNext = pageNext;
    buttons[nbButtons].buttonLeft = buttonLeft;
    buttons[nbButtons].buttonRight = buttonRight;
    buttons[nbButtons].order = order;
    buttons[nbButtons].function = function;
    nbButtons++;
}


void drawMenuText(){
    button b;
    for(int i = 0; i < nbButtons; i++){
        b = buttons[i];
        if(b.pageCurrent == page){
            DrawText(b.text,b.pos.x,b.pos.y,b.textSize,b.textColor);
            if(b.order == selection){
                DrawText("*", b.pos.x - 30, b.pos.y, b.textSize, b.textColor);
            }
        }
    }
}


// --------------- Fonctions de pages --------------------- //


void drawPage_MAIN_MENU(){
    DrawText("TOUHOU_C", 50, 200, 80, RED);
}

void drawPage_KEYBINDS(){
    DrawText("CONTROLS", 50, 170, 60, RED);
}

void drawPages(){
    switch((int)page)
    {
    case MAIN_MENU:
        drawPage_MAIN_MENU();
        break;
    case KEYBINDS:
        drawPage_KEYBINDS();
        break;
    }
}


// -------------------------------------------------------- //

void updateMenu(){
    int nbButtonsPage = 0;
    int i;
    //On compte le nombre de boutons sur la page en cours d'affichage
    for(i = 0; i< nbButtons; i++){
        nbButtonsPage += (page == buttons[i].pageCurrent);
    }

    if(IsKeyPressed(globals.keybind_move_down) && selection < nbButtonsPage-1){
        (selection)++;
    } 
    if(IsKeyPressed(globals.keybind_move_up) && selection > 0){
        (selection)--;
    }
    if(IsKeyPressed(globals.keybind_move_left)){
        for(i=0; (buttons[i].pageCurrent!=page || buttons[i].order!=selection)&&(i<nbButtons); i++);
        if(buttons[i].buttonLeft != NO_BUTTON) selection=buttons[i].buttonLeft;
    }
    if(IsKeyPressed(globals.keybind_move_right)){
        for(i=0; (buttons[i].pageCurrent!=page || buttons[i].order!=selection)&&(i<nbButtons); i++);
        if(buttons[i].buttonRight != NO_BUTTON) selection=buttons[i].buttonRight;
    }

    if(IsKeyPressed(globals.keybind_validate)){
        for(i = 0; i < nbButtons; i++){
            if(selection == buttons[i].order && page == buttons[i].pageCurrent){
                
                if(buttons[i].function != NULL){
                    buttons[i].function();
                }
                
                if(buttons[i].pageNext != page){
                    page = buttons[i].pageNext;
                    selection = 0;
                }
                break;  // ce break est essentiel: après avoir changé de page il ne faut surtout pas
                        // continuer de parcourir les boutons au risque de refaire des changements
            }
        }
    }
}



void menu(){
    updateMenu();
    
    BeginDrawing();
        ClearBackground(BLACK);


        drawPages();
        drawMenuText();
    EndDrawing(); 
}

void pauseGame(){
    if(IsKeyPressed(globals.keybind_pause)){
        globals.pause = !globals.pause;
    }
}

void pauseMenu(){
    DrawText("PAUSE", 100, 300, 50, RED);
    DrawRectangleLines(50, 50, PANEL_WIDTH - 100, PANEL_HEIGHT - 100, WHITE);
}