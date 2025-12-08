#ifndef ENEMY_H
#define ENEMY_H

#include "include/raylib.h"
#include "entity.h"

#define MAX_ENEMIES 100

typedef struct enemyTemp {
    Entity entity;
    int hp;
} Enemy;

void EnemyInit(Enemy* enemy, Vector2 pos, Vector2 direction, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp);
void SpawnEnemy(Vector2 pos, Vector2 direction, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp);
void SpawnEnemyPol(Vector2 pos, float angle, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp);
void UpdateEnemy(Enemy* enemy);
void UpdateEnemies();

#endif