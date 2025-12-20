#ifndef ASSETS_H
#define ASSETS_H

#include "include/raylib.h"
#include "include/raymath.h"



enum {
    BULLET_SPRITESHEET,
    BOSS_SPRITESHEET,
    ANIM_TEST_SPRITESHEET,
    REIMU_SPRITESHEET,
    HITBOX_SPRITESHEET,
    MAX_TEXTURES
};

extern Texture2D textures[MAX_TEXTURES];

void AssetsLoad();
void AssetsUnload();

#endif