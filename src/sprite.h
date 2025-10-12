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

typedef struct {
    Sprite sprite;
    char* name;
} SpriteEntry;

typedef struct {
    SpriteEntry spritesTab[MAX_SPRITES];
    int nbSprites;
} Sprites;

typedef enum {
    BALL_M_BLACK,
    ANIM_TEST
} BulletType;

void SpriteInit(Sprite* sprite, char* texture_name, int nbFrames, float animSpeed, Vector2 collisionOffset, float collisionRadius);
void LoadBulletSprites();
void UpdateAnimation(Sprite* sprite);

#endif