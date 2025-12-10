#ifndef ENEMY_H
#define ENEMY_H

#include "include/raylib.h"
#include "entity.h"

#define MAX_ENEMIES 1000

typedef struct enemyTemp {
    Entity entity;
    int hp;
    int id; //cet identifiant est unique. Il sert à référencer l'ennemi dans toutes les bullets filles. 
} Enemy;

unsigned long EnemyInit(Enemy* enemy, Vector2 pos, Vector2 direction, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp);
unsigned long SpawnEnemy(Vector2 pos, Vector2 direction, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp);
unsigned long SpawnEnemyPol(Vector2 pos, float angle, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp);
void UpdateEnemy(Enemy* enemy);
void UpdateEnemies();

#endif