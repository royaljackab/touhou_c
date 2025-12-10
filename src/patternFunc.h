#ifndef PATTERNFUNC_H
#define PATTERNFUNC_H

#include "include/raylib.h"
#include "entity.h"
#include "bullet.h"

typedef enum {
    NB_BULLETS,
    SPEED,
    CIRCLE_FRAME,
    GENERATION,
    GEN_MAX
} SpawnCircleData;

void Pattern_Straight(Entity* bullet, float userData[MAX_DATA]);
void Pattern_SineWave(Entity* bullet, float userData[MAX_DATA]);
void Pattern_SpawnCircle(Entity* bullet, float userData[MAX_DATA]);
void Pattern_Gravity(Entity* bullet, float userData[MAX_DATA]);
void Pattern_Test(Entity* bullet, float userData[MAX_DATA]);
#endif