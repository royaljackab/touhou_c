#ifndef MENU_H
#define MENU_H

#include "sprite.h"
#include "../include/raylib.h"
#include "task.h"
#include "globals.h"

#define MAX_BUTTONS 1000
#define NO_BUTTON -1

typedef enum{
    MAIN_MENU,
    OPTIONS1,
    KEYBINDS,
} pageMenu;

// Peut-être ça servira un jour
// EDIT: ce jour est arrivé (25/01/2026)
typedef struct{
    Sprite sprite;
    Vector2 pos;

    //Ces attributs ont vocation à disparaitre, remplacés par des sprites
    char text[50];
    int textSize;
    Color textColor;

    pageMenu pageCurrent; //page sur laquelle on trouve ce bouton
    pageMenu pageNext; //page vers laquelle envoie ce bouton
    int order; //la valeur de "selection" qui correspond à ce bouton
    int buttonLeft;
    int buttonRight;

    void (*function)(void); //traitement à réaliser par le bouton
    // note: le traitement prend void en paramètre, ce qui pourrait poser problème.
    // les principaux cas à traiter seront:
    // - changer le game_state
    // - changer une option
    // Ces cas ne semblent pas nécessiter de paramètres: on accepte de ne pas en avoir.
    // (autrement il faudrait certainement un USERDATA)
} button;

void updateMenu             ();
void drawMenuText           ();
void drawPage_MAIN_MENU     ();
void drawPages              ();
void menu                   ();
void pauseGame              ();
void pauseMenu              ();
void Button_Create_Sprite   (Sprite sprite, int x, int y, pageMenu pageCurrent, pageMenu pageNext, int buttonLeft, int buttonRight, int order, void (*function)(void));
void Button_Create_Text     (int x, int y, char * text, int textSize, Color color, pageMenu pageCurrent, pageMenu pageNext, int buttonLeft, int buttonRight, int order, void (*function)(void));

#endif