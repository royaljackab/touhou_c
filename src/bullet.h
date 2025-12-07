#ifndef BULLET_H
#define BULLET_H

#define BULLET_PATTERN_FUNC void (*pattern)(struct bulletTemp* bullet, float userData[MAX_DATA])

#include "include/raylib.h"
#include "assets.h"
#include "sprite.h"

struct Player;
typedef struct Player Player;

#define MAX_BULLETS 10000
#define MAX_DATA 10

typedef struct bulletTemp {

    Sprite sprite;

    Vector2 pos; //Center
    Vector2 location; //Corner Up-Left for drawing
    Vector2 direction;
    float speed;

    int timer;
    void (*pattern)(struct bulletTemp* bullet, float userData[MAX_DATA]);
    float userData[MAX_DATA];

    int bActive;
    int bVisible;
    int bDamage;
} Bullet;

#include "patternFunc.h"

void BulletInit(Bullet* bullet, Vector2 pos, Vector2 direction, float speed, BULLET_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible);
void UpdateBullet(Bullet* bullet);
void UpdateBullets();
void ShowBulletHitbox(Bullet* bullet);
void SpawnBullet(Vector2 pos, Vector2 direction, float speed, BULLET_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible);
void SpawnBulletPol(Vector2 pos, float angle, float speed, BULLET_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible);
void SpawnBulletCircle(int nbBullets, Vector2 pos, float angle, float speed, BULLET_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible);
void SpawnBulletToPlayer(Vector2 pos, Player player, float speed, BULLET_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible);
void Rotate_Bullet(Bullet* bullet, float angle);
#endif
