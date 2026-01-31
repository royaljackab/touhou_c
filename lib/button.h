#ifndef MENU_H
#define MENU_H

// #include "../include/raylib.h"
#include "globals.h"
#include "input.h"

#define MAX_BUTTONS 30
#define NO_BUTTON -1

typedef struct{
    Vector2 pos;
    int buttonLeft;
    int buttonRight;
    int validated;

    //ces champs ont vocation a disparaitre
    char * text;
    int size;
    Color color;
} Button;

typedef struct{
    Button buttons[MAX_BUTTONS];
    int selection;
    int nbButtons;
} ButtonSystem;

int button_is_validated             (ButtonSystem *buttonSystem);
void button_update                  (ButtonSystem *buttonSystem, InputState *inputState);
void button_create                  (ButtonSystem *buttonSystem, int x, int y);
void button_create_ex               (ButtonSystem *buttonSystem, int x, int y, int left, int right);
void button_create_text             (ButtonSystem *buttonSystem, int x, int y, char * text, int size, Color color);
void button_create_text_ex          (ButtonSystem *buttonSystem, int x, int y, char * text, int size, Color color, int left, int right);
ButtonSystem button_system_init     ();

void button_create_text             (ButtonSystem *buttonSystem, int x, int y, char * text, int size, Color color);
void draw_cursor                    (ButtonSystem *buttonSystem);
void draw_text                      (ButtonSystem *buttonSystem);

#endif