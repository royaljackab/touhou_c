#ifndef GLOBAL_H
#define GLOBAL_H

#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include "assets.h"
#include "sprite.h"
#include "bullet.h"
#include "patternFunc.h"

#define PANEL_WIDTH 500
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define MAX_SPRITES 300

#define TRUE 1
#define FALSE 0

#define VECTOR_NULL (Vector2){0,0}
#define MIDDLE_SCREEN (Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT/2}

extern Assets assets;
extern Sprite bulletSprites[MAX_SPRITES];
extern Bullet bullets[MAX_BULLETS];
extern int nbBullets;

#endif