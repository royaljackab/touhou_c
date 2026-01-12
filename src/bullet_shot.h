#ifndef BULLET_SHOT_H
#define BULLET_SHOT_H

#include "bullet_sprites.h"

ObjID CreateShot(float x, float y, float speed, float angle, BulletGraphic graphic, int delay);
ObjID CreateLaser(float x, float y, float angle, float length, float maxWidth, int deleteTime, BulletGraphic graphic, int delay);
ObjID CreateLooseLaser(float x, float y, float speed, float angle, float length, float width, int graphic, int delay);

#endif