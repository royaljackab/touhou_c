#include "bullet_sprites.h"

Sprite bulletSprites[MAX_TEXTURES];

void Load_BulletSprites() {

    SetTexture(&bulletSprites[ANIM_TEST], ANIM_TEST_SPRITESHEET);
    SetSourceRect(&bulletSprites[ANIM_TEST], 0,0,256,16);
    SetAnimation(&bulletSprites[ANIM_TEST], 16, 2);
    SetCollisionRadius(&bulletSprites[ANIM_TEST], 5);

    SetTexture(&bulletSprites[BALL_M_BLACK], BULLET_SPRITESHEET);
    SetSourceRect(&bulletSprites[BALL_M_BLACK], 5, 54, 16, 16);
    SetCollisionRadius(&bulletSprites[BALL_M_BLACK], 5);
}

void ObjSprite2D_SetBulletSprite(ObjID id, BulletGraphic graphic) {
    if (id==ID_INVALID) return;
    objects[id].sprite = bulletSprites[graphic];
}