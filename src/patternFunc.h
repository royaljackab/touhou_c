#ifndef PATTERNFUNC_H
#define PATTERNFUNC_H

#include "include/raylib.h"
#include "bullet.h"

typedef enum {
    NB_BULLETS,
    SPEED,
    CIRCLE_FRAME,
    GENERATION,
    GEN_MAX
} SpawnCircleData;

void Pattern_Straight(Bullet* bullet, int userData[MAX_DATA]);
void Pattern_SineWave(Bullet* bullet, int userData[MAX_DATA]);
void Pattern_SpawnCircle(Bullet* bullet, int userData[MAX_DATA]);
#endif 