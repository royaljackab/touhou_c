#ifndef BULLET_SPRITES_H
#define BULLET_SPRITES_H

#include "obj.h"

typedef enum {
    BALL_M_BLACK,
    ANIM_TEST
} BulletGraphic;

extern Sprite bulletSprites[MAX_TEXTURES];

void Load_BulletSprites();
void ObjSprite2D_SetBulletSprite(ObjID id, BulletGraphic graphic);

#endif