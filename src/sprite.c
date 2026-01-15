#include "sprite.h"
#include "globals.h"

void SetTexture(Sprite* sprite, int textureID) {
    sprite->textureID = textureID;
    sprite->srcRect = (Rectangle){0,0,textures[textureID].width, textures[textureID].height};
    sprite->center = (Vector2){textures[textureID].width/2, textures[textureID].height/2}; //Par défaut, le milieu
    sprite->isAnimated = false;
    sprite->color = WHITE;
    sprite->rotation = 0;
    sprite->scale = (Vector2){1,1};
}

void SetSourceRect(Sprite* sprite, float x, float y, float width, float height) {
    sprite->srcRect = (Rectangle){x,y,width,height};
    sprite->center = (Vector2){width/2, height/2};
}

void SetCenter(Sprite* sprite, float x, float y) {
    sprite->center = (Vector2){x,y}; 
}

void SetRotation(Sprite* sprite, float rotation) {
    sprite->rotation = rotation;
}

void SetScale(Sprite* sprite, float x, float y) {
    sprite->scale = (Vector2){x,y};
}

void SetColor(Sprite* sprite, Color color) {
    sprite->color = color;
}

void SetAnimation(Sprite* sprite, int frameCount, int delay) {
    sprite->isAnimated = true;
    sprite->animFrameCount = frameCount;
    sprite->srcRect.width = sprite->srcRect.width / frameCount;
    sprite->frameWidth = sprite->srcRect.width;
    sprite->animStart = (Vector2){sprite->srcRect.x,sprite->srcRect.y};
    sprite->center = (Vector2){sprite->srcRect.width/2, sprite->srcRect.height/2};
    sprite->animSpeed = delay;
    sprite->animTimer = 0;
    sprite->currentFrame = 0;
}

void SetCollisionRadius(Sprite* sprite, float radius) {
    sprite->hitboxRadius = radius;
}

void UpdateAnimation(Sprite* sprite) {
    sprite->animTimer++;

    if(sprite->animTimer >= sprite->animSpeed) {
        sprite->animTimer=0;
        sprite->currentFrame = (sprite->currentFrame + 1) % sprite->animFrameCount;
        sprite->srcRect.x = sprite->animStart.x + sprite->frameWidth * sprite->currentFrame;
    }
}

void DrawSprite(Sprite sprite, Vector2 pos) {
    Texture2D tex = textures[sprite.textureID];

    Rectangle destRec = {
        pos.x,
        pos.y,
        sprite.srcRect.width * sprite.scale.x,
        sprite.srcRect.height * sprite.scale.y
    };

    DrawTexturePro(tex, sprite.srcRect, destRec, sprite.center, sprite.rotation, sprite.color);
}