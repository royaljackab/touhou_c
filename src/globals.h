#ifndef GLOBAL_H
#define GLOBAL_H

#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "include/raylib.h"
#include "include/raymath.h"
#include "assets.h"
#include "sprite.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "patternFunc.h"

#define PANEL_WIDTH 500
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define MAX_SPRITES 300

#define TRUE 1
#define FALSE 0

#define VECTOR_NULL (Vector2){0,0}
#define MIDDLE_SCREEN (Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT/2}
#define MIDDLE_BOSS (Vector2){SCREEN_WIDTH/2, 200}

#define MoveWithinGameX(pos) pos = Clamp(pos, PANEL_WIDTH, SCREEN_WIDTH - PANEL_WIDTH)
#define MoveWithinGameY(pos) pos = Clamp(pos, 0, SCREEN_HEIGHT)
#define MoveWithinGameVec(pos) MoveWithinGameX(pos.x); MoveWithinGameY(pos.y);

#define AngleToV(v1,v2) atan((v2.y - v1.y)/(v2.x - v1. x))
#define AngleToPlayer(src, player) AngleToV(src, player.pos)

extern Assets assets;
extern Sprite bulletSprites[MAX_SPRITES];
extern Bullet bullets[MAX_BULLETS];
extern Enemy enemies[MAX_ENEMIES];
extern int nbBullets;
extern int nbEnemies;
extern int debug;
extern unsigned long idCounterEnemy;

extern Player player1;

#endif