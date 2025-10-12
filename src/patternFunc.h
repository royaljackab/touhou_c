#ifndef PATTERNFUNC_H
#define PATTERNFUNC_H

#include "include/raylib.h"
#include "bullet.h"

void Pattern_Straight(Bullet* bullet, void* userData);
void Pattern_SineWave(Bullet* bullet, void* userData);
void Pattern_SpawnCircle(Bullet* bullet, void* userData);
#endif 