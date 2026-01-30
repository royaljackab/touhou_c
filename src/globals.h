#ifndef GLOBALS_H
#define GLOBALS_H

#define DRAW_MARGIN 500   // 80
#define SCREEN_WIDTH 1280 // 1280
#define SCREEN_HEIGHT 900 // 900

#define PANEL_LEFT SCREEN_WIDTH / 64      // 10
#define PANEL_WIDTH SCREEN_WIDTH / 2      // 700
#define PANEL_UP SCREEN_HEIGHT / 45       // 20
#define PANEL_HEIGHT SCREEN_HEIGHT * 0.95 // 820

#define MAX_TEXTURES 200
#define MAX_OBJECTS 10000

#include "input.h"
#include "obj.h"
#include "sprite.h"

typedef enum { TITLE_SCREEN, STAGE1, MOONLIGHT } gameState;

typedef struct {
  gameState gameState;
  int pause;
  input_state inputState;
  input_config inputConfig;
} varGlobals;

extern varGlobals globals;
extern Texture2D textures[MAX_TEXTURES];
extern Sprite bulletSprites[MAX_TEXTURES];
extern Object objects[MAX_OBJECTS];

#endif
