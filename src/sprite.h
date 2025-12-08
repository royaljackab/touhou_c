#ifndef SPRITE_H
#define SPRITE_H

#include "include/raylib.h"

#define MAX_SPRITES 300

typedef struct {

    Texture2D spritesheet;
    int nbFrames;
    float animSpeed;
    int currentFrame;
    int frameCounter;

    Rectangle frameRec;
    Vector2 collisionOffset;
    float collisionRadius;

} Sprite;

typedef enum {
    BALL_M_BLACK,
    ANIM_TEST,
    REIMU_STILL,
    REIMU_LEFT,
    REIMU_RIGHT,
    REIMU_PINK_AMULET,
    HITBOX,
    FAIRY_S_BLUE_STILL
} BulletType; 

void SpriteInitRec(Sprite* sprite, char* texture_name, int nbFrames, float animSpeed, Vector2 collisionOffset, float collisionRadius, int x, int y, int width, int height);
void SpriteInit(Sprite* sprite, char* texture_name, int nbFrames, float animSpeed, Vector2 collisionOffset, float collisionRadius);
void LoadBulletSprites();
void UpdateAnimation(Sprite* sprite);
Vector2 SpriteCenter(Sprite sprite);

#endif