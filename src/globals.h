#ifndef GLOBALS_H
#define GLOBALS_H

#define DRAW_MARGIN 80                          //80
#define SCREEN_WIDTH 1280                       //1280
#define SCREEN_HEIGHT 900                       //900

#define PANEL_LEFT SCREEN_WIDTH/128             //10
#define PANEL_WIDTH SCREEN_WIDTH/2              //700
#define PANEL_UP SCREEN_HEIGHT/45               //20
#define PANEL_HEIGHT SCREEN_HEIGHT-DRAW_MARGIN  //820



typedef enum{
    TITLE_SCREEN,
    STAGE1,
    MOONLIGHT
} gameState;

typedef struct{
    gameState gameState;
    int pause;
} varGlobals;

extern varGlobals globals;

#endif