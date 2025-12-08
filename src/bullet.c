#include "globals.h"
#include "bullet.h"

void BulletInit(Bullet* bullet, Vector2 pos, Vector2 direction, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible) {
    EntityInit(bullet, pos, direction, speed, pattern, userData, type, damage, visible);
    bullets[nbBullets++] = *bullet;
}

void UpdateBullets() {
    for (int i = 0; i < nbBullets; i++) {
        UpdateEntity(&bullets[i]);
        bullets[i].pattern(&bullets[i], bullets[i].userData);

        if (!bullets[i].bActive) {
            //On échange avec le dernier et on décrémente
            bullets[i] = bullets[nbBullets - 1];
            nbBullets--;
            i--; //Il faut repasser sur l'index i donc
        }
    }
}

void SpawnBullet(Vector2 pos, Vector2 direction, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible) {
    if (nbBullets >= MAX_BULLETS) return; 

    Bullet bullet;
    BulletInit(&bullet, pos, direction, speed, pattern, userData, type, damage, visible);

}

void SpawnBulletPol(Vector2 pos, float angle, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible) {
    /**
     * Spawn Bullet mais coordonnées polaires
     */
    Vector2 direction = {cos( PI * angle / 180.f), sin( PI * angle / 180.f)};
    SpawnBullet(pos, direction, speed, pattern, userData, type, damage, visible);
}


void SpawnBulletCircle(int nbBullets, Vector2 pos, float angle, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible) {
    for (int i=0; i<nbBullets; i++) {
        SpawnBulletPol(pos, angle + i * 360 / nbBullets, speed, pattern, userData, type, damage, visible);
    }
}

void SpawnBulletToPlayer(Vector2 pos, Player player, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible) {
    Vector2 srcToPlayer = Vector2Subtract(player.pos, pos);

    SpawnBullet(pos, srcToPlayer, 5, pattern, userData, type, damage, visible);
}


