#ifndef ENEMY_H
#define ENEMY_H

#include "include/raylib.h"
#include "assets.h"
#include "sprite.h"

#define ENEMY_PATTERN_FUNC void (*pattern)(struct bulletTemp* bullet, float userData[MAX_DATA])

void EnemyInit(Bullet* enemy, Vector2 pos, Vector2 direction, float speed, ENEMY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp);
void SpawnEnemy(Vector2 pos, Vector2 direction, float speed, ENEMY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp);
void SpawnEnemyPol(Vector2 pos, float angle, float speed, ENEMY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp);
void UpdateEnemies();
#endif