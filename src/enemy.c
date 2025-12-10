#include "globals.h"
#include "enemy.h"

unsigned long EnemyInit(Enemy* enemy, Vector2 pos, Vector2 direction, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp) {
    enemy->hp = hp;
    enemy->id = idCounterEnemy++;
    // printf("l'ennemi %d est ne\n",enemy->id);
    EntityInit(&enemy->entity, pos, direction, speed, pattern, userData, type, damage, visible);
    

    enemies[nbEnemies++] = *enemy;
    return enemy->id;
}

unsigned long SpawnEnemy(Vector2 pos, Vector2 direction, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp) {
    if (nbEnemies >= MAX_ENEMIES) return 0;
    Enemy enemy;
    return EnemyInit(&enemy, pos, direction, speed, pattern, userData, type, damage, visible, hp);
}

unsigned long SpawnEnemyPol(Vector2 pos, float angle, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp) {
    /**
     * SpawnEnemy mais coordonnées polaires
     */
    Vector2 direction = {cos( PI * angle / 180.f), sin( PI * angle / 180.f)};
    return SpawnEnemy(pos, direction, speed, pattern, userData, type, damage, visible, hp);
}

void UpdateEnemy(Enemy* enemy) {
    UpdateEntity(&enemy->entity);
    // Check si l'ennemi prend des dégats d'un tir du joueur
    for (int i=0; i<nbBullets; i++) {
        Entity entityB = bullets[i].entity;
        if(entityB.bDamage == 2 && CheckCollisionCircles(entityB.pos, entityB.sprite.collisionRadius, enemy->entity.pos, enemy->entity.sprite.collisionRadius)) {
            enemy->hp -= entityB.bDamage;
        }
    }
}

void UpdateEnemies() {
    // Pour les ennemis, on peut réutiliser la fonction UpdateEntity, mais pas la fonction UpdateBullets qui travaille un tableau spécifique.

    for (int i = 0; i < nbEnemies; i++) {
        UpdateEnemy(&enemies[i]);
        enemies[i].entity.pattern(&enemies[i].entity, enemies[i].entity.userData);

        if (!enemies[i].entity.bActive || enemies[i].hp <= 0) {
            //On échange avec le dernier et on décrémente
            // printf("un ennemi est mort: %d\n", enemies[i].id);
            enemies[i] = enemies[nbEnemies - 1];
            nbEnemies--;
            i--; //Il faut repasser sur l'index i donc
        }
    }
}