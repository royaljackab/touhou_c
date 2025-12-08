#ifndef BULLET_H
#define BULLET_H

#include "include/raylib.h"
#include "entity.h"

struct Player;
typedef struct Player Player;

typedef Entity Bullet;

void BulletInit(Bullet* bullet, Vector2 pos, Vector2 direction, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible);
void UpdateBullets();
void SpawnBullet(Vector2 pos, Vector2 direction, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible);
void SpawnBulletPol(Vector2 pos, float angle, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible);
void SpawnBulletCircle(int nbBullets, Vector2 pos, float angle, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible);
void SpawnBulletToPlayer(Vector2 pos, Player player, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible);

#endif
