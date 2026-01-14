#ifndef MENU_H
#define MENU_H

#include "sprite.h"
#include "include/raylib.h"
#include "task.h"
#include "globals.h"

#define NB_BUTTONS 2

// Peut-être ça servira un jour
typedef struct{
    Sprite sprite;
    Vector2 pos;
} button;

void updateMenu (gameState *gameState, int* selection);
void drawMenu   (int selection);
void menu       ();
void pauseGame  ();
void pauseMenu  ();

#endif