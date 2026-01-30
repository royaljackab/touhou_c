#ifndef SPRITE_H
#define SPRITE_H

#include "../include/raylib.h"
#include <stdbool.h>

#include "assets.h"

typedef struct {
    int textureID;
    Rectangle srcRect;
    Vector2 center;
    Vector2 scale;
    Color color;
    int renderPriority; //Pour afficher devant/derriere d'autres..

    //Pour l'animation
    bool isAnimated;
    int animFrameCount;
    int animSpeed;
    int animTimer;
    int currentFrame;
    int frameWidth;
    float rotation;
    Vector2 animStart;

    float hitboxRadius;
} Sprite;

void SetTexture        (Sprite* sprite, int textureID);
void SetSourceRect     (Sprite* sprite, float x, float y, float width, float height);
void SetCenter         (Sprite* sprite, float x, float y);
void SetRotation       (Sprite* sprite, float rotation);
void SetScale          (Sprite* sprite, float x, float y);
void SetColor          (Sprite* sprite, Color color);
void SetAnimation      (Sprite* sprite, int frameCount, int delay);
void SetCollisionRadius(Sprite* sprite, float radius);
void UpdateAnimation   (Sprite* sprite);
void DrawSprite        (Sprite sprite, Vector2 pos);

#endif