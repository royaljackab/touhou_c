#ifndef ENEMY_H
#define ENEMY_H

#include "include/raylib.h"
#include "assets.h"
#include "sprite.h"
#include "bullet.h"

#define MAX_ENEMIES 100
#define ENEMY_PATTERN_FUNC void (*pattern)(struct bulletTemp* bullet, float userData[MAX_DATA])

typedef struct enemyTemp {
    Entity entity;
    int hp;
} Enemy;

void EnemyInit(Enemy* enemy, Vector2 pos, Vector2 direction, float speed, ENEMY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp);
void SpawnEnemy(Vector2 pos, Vector2 direction, float speed, ENEMY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp);
void SpawnEnemyPol(Vector2 pos, float angle, float speed, ENEMY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp);
void UpdateEnemy(Enemy* enemy);
void UpdateEnemies();
#endif