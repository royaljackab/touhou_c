#include "globals.h"
#include "assets.h"
#include "sprite.h"


void SpriteInit(Sprite* sprite, char* texture_name, int nbFrames, float animSpeed, Vector2 collisionOffset, float collisionRadius) {
    sprite->spritesheet = GetTexture(texture_name);

    sprite->animSpeed = animSpeed;
    sprite->nbFrames = nbFrames;

    sprite->frameRec.x = sprite->frameRec.y = 0;
    sprite->frameRec.height = sprite->spritesheet.height;
    sprite->frameRec.width = sprite->spritesheet.width / sprite->nbFrames;

    sprite->currentFrame = 0;
    sprite->frameCounter = 0;

    sprite->collisionOffset = collisionOffset;
    sprite->collisionRadius = collisionRadius;
}

void LoadBulletSprites() {
    Sprite sprite;

    SpriteInit(&sprite, "ball_m_black", 1, 1, (Vector2){8,8}, 2);
    bulletSprites[BALL_M_BLACK] = sprite;

    SpriteInit(&sprite, "anim_test", 16, 60, (Vector2){16,16}, 8);
    bulletSprites[ANIM_TEST] =sprite;

    SpriteInit(&sprite, "reimu_still", 8, 30, (Vector2){16,48}, 16);
    bulletSprites[REIMU_STILL] =sprite;

    SpriteInit(&sprite, "reimu_left", 8, 30, (Vector2){16,48}, 16);
    bulletSprites[REIMU_LEFT] = sprite;

    SpriteInit(&sprite, "reimu_right", 8, 30, (Vector2){16,48}, 16);
    bulletSprites[REIMU_RIGHT] = sprite;
}

void UpdateAnimation(Sprite* sprite) {
    sprite->frameCounter++;

    if (sprite->frameCounter >= sprite->animSpeed / sprite->nbFrames) {

        sprite->frameCounter = 0;
        sprite->currentFrame = (sprite->currentFrame + 1) % sprite->nbFrames;
        sprite->frameRec.x = sprite->currentFrame * sprite->frameRec.width;
    }
}




