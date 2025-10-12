#ifndef BULLET_H
#define BULLET_H

#define BULLET_PATTERN_FUNC void (*pattern)(struct bulletTemp* bullet, void* userData)

#include "include/raylib.h"
#include "assets.h"
#include "sprite.h"


#define MAX_BULLETS 1000

typedef struct bulletTemp {

    Sprite sprite;

    Vector2 pos; //Center
    Vector2 location; //Corner Up-Left for drawing
    Vector2 direction;
    float speed;

    float timer;
    void (*pattern)(struct bulletTemp* bullet, void* userData);
    void* userData;

    int bActive;
    int bDamage;
} Bullet;

#include "patternFunc.h"

void BulletInit(Bullet* bullet, Vector2 pos, Vector2 direction, float speed, BULLET_PATTERN_FUNC, BulletType type, int damage);
void UpdateBullet(Bullet* bullet);
void UpdateBullets();
void SpawnBullet(Vector2 pos, Vector2 direction, float speed, BULLET_PATTERN_FUNC, BulletType type, int damage);
void SpawnBulletAngle(Vector2 pos, float angle, float speed, BULLET_PATTERN_FUNC, BulletType type, int damage);
void SpawnBulletCircle(int nbBullets, Vector2 pos, float angle, float speed, BULLET_PATTERN_FUNC, BulletType type, int damage);

#endif
