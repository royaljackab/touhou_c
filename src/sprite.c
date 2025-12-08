#include "globals.h"
#include "assets.h"
#include "sprite.h"

#define CENTER_SPRITE(str) (Vector2){GetTexture(str).width/2, GetTexture(str).height/2}


void SpriteInitRec(Sprite* sprite, char* texture_name, int nbFrames, float animSpeed, Vector2 collisionOffset, float collisionRadius, int x, int y, int width, int height) {
    sprite->spritesheet = GetTexture(texture_name);

    sprite->animSpeed = animSpeed;
    sprite->nbFrames = nbFrames;

    sprite->frameRec.x = x;
    sprite->frameRec.y = y;
    sprite->frameRec.height = height;
    sprite->frameRec.width = width / nbFrames;

    sprite->currentFrame = 0;
    sprite->frameCounter = 0;

    sprite->collisionOffset = collisionOffset;
    sprite->collisionRadius = collisionRadius;
}

void SpriteInit(Sprite* sprite, char* texture_name, int nbFrames, float animSpeed, Vector2 collisionOffset, float collisionRadius) {
    SpriteInitRec(sprite, texture_name, nbFrames, animSpeed, collisionOffset, collisionRadius, 0, 0, GetTexture(texture_name).width, GetTexture(texture_name).height);
}

void LoadBulletSprites() {
    Sprite sprite;

    SpriteInit(&sprite, "ball_m_black", 1, 1, (Vector2){8,8}, 5);
    bulletSprites[BALL_M_BLACK] = sprite;

    SpriteInit(&sprite, "anim_test", 16, 60, (Vector2){16,16}, 8);
    bulletSprites[ANIM_TEST] =sprite;

    SpriteInit(&sprite, "reimu_still", 8, 30, (Vector2){16,24}, 16);
    bulletSprites[REIMU_STILL] =sprite;

    SpriteInit(&sprite, "reimu_left", 8, 30, (Vector2){16,24}, 16);
    bulletSprites[REIMU_LEFT] = sprite;

    SpriteInit(&sprite, "reimu_right", 8, 30, (Vector2){16,24}, 16);
    bulletSprites[REIMU_RIGHT] = sprite;

    SpriteInit(&sprite, "reimu_pink_amulet", 1, 1, (Vector2){8,10}, 8);
    bulletSprites[REIMU_PINK_AMULET] = sprite;

    SpriteInit(&sprite, "hitbox", 1, 1, CENTER_SPRITE("hitbox"), 3);
    bulletSprites[HITBOX] = sprite;

    SpriteInit(&sprite, "fairy_s_blue_still", 4, 30, (Vector2){24,16}, 6);
    bulletSprites[FAIRY_S_BLUE_STILL] = sprite;

    
}

void UpdateAnimation(Sprite* sprite) {
    sprite->frameCounter++;

    if (sprite->frameCounter >= sprite->animSpeed / sprite->nbFrames) {

        sprite->frameCounter = 0;
        sprite->currentFrame = (sprite->currentFrame + 1) % sprite->nbFrames;
        sprite->frameRec.x = sprite->currentFrame * sprite->frameRec.width;
    }
}

Vector2 SpriteCenter(Sprite sprite) {
    /**
     * Renvoie le centre d'un sprite
     */

    Vector2 location = (Vector2){sprite.frameRec.x, sprite.frameRec.y};
    return Vector2Add(location, sprite.collisionOffset);
}

