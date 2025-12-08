#include "globals.h"
#include "enemy.h"

void EnemyInit(Bullet* enemy, Vector2 pos, Vector2 direction, float speed, ENEMY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp) {
    enemy->pos = pos;
    enemy->sprite = bulletSprites[type];
    enemy->speed = speed; 
    enemy->hp = hp;

    enemy->location = (Vector2){pos.x - enemy->sprite.collisionOffset.x, pos.y - enemy->sprite.collisionOffset.y};
    enemy->direction = Vector2Normalize(direction);
    enemy->pattern = pattern;
    memcpy(enemy->userData, userData, sizeof(float)*MAX_DATA);

    enemy->bActive = TRUE;
    enemy->bDamage = damage;
    enemy->bVisible = visible;
    enemy->bEnemy = 1;
    enemy->timer = 0;

    enemies[nbEnemies++] = *enemy;
}

void SpawnEnemy(Vector2 pos, Vector2 direction, float speed, ENEMY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp) {
    if (nbEnemies >= MAX_BULLETS) return; 
    if (nbEnemies >= MAX_ENEMIES) return;
    Bullet enemy;
    EnemyInit(&enemy, pos, direction, speed, pattern, userData, type, damage, visible, hp);

}

void SpawnEnemyPol(Vector2 pos, float angle, float speed, ENEMY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, int hp) {
    /**
     * SpawnEnemy mais coordonnées polaires
     */
    Vector2 direction = {cos( PI * angle / 180.f), sin( PI * angle / 180.f)};
    SpawnEnemy(pos, direction, speed, pattern, userData, type, damage, visible, hp);
}

void UpdateEnemies() {
    // Pour les ennemis, on peut réutiliser la fonction UpdateBullet, mais pas la fonction UpdateBullets qui travaille un tableau spécifique.

    for (int i = 0; i < nbEnemies; i++) {
        UpdateBullet(&enemies[i]);
        enemies[i].pattern(&enemies[i], enemies[i].userData);

        if (!enemies[i].bActive) {
            //On échange avec le dernier et on décrémente
            enemies[i] = enemies[nbEnemies - 1];
            nbEnemies--;
            i--; //Il faut repasser sur l'index i donc
        }
    }
}