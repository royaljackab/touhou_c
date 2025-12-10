#include "globals.h"
#include "bullet.h"

void PrintBullet(Bullet* bullet){
    // Fonction de test pour afficher une bullet dans la console.
    printf("-- Information de l'entity: --\n");
    printf("-- Information du parent: --\n");
}


void BulletInit(Bullet* bullet, Vector2 pos, Vector2 direction, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, unsigned long idParent) {
    bullet->idParent = idParent;
    // printf("%d est ne: son parent est %d\n",bullet ,bullet->idParent);
    EntityInit(&bullet->entity, pos, direction, speed, pattern, userData, type, damage, visible);
    bullets[nbBullets++] = *bullet;
}

void UpdateBullet(Bullet* bullet) {
    UpdateEntity(&bullet->entity);

    // Si le parent est inactif on considère que la bullet n'a plus de parent
    if(bullet->idParent == 0) return;
    int parentAlive = 0;
    for(int i=0; i<nbEnemies ; i++){
        if(bullet->idParent == enemies[i].id){
            // printf("%d a pour parent: %d\n",bullet ,bullet->idParent);
            parentAlive = 1;
        }
    }
    if(parentAlive == 0){
        // printf("%d avait pour parent: %d mais il est mort\n",bullet ,bullet->idParent);
        bullet->idParent = 0;
    }
}

void UpdateBullets() {
    for (int i = 0; i < nbBullets; i++) {
        UpdateBullet(&bullets[i]);
        bullets[i].entity.pattern(&bullets[i].entity, bullets[i].entity.userData);

        if (!bullets[i].entity.bActive) {
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
    BulletInit(&bullet, pos, direction, speed, pattern, userData, type, damage, visible, 0);

}

void SpawnBulletPol(Vector2 pos, float angle, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible) {
    /**
     * SpawnBullet mais coordonnées polaires
     */
    Vector2 direction = {cos( PI * angle / 180.f), sin( PI * angle / 180.f)};
    SpawnBullet(pos, direction, speed, pattern, userData, type, damage, visible);
}

void SpawnBulletParent(Vector2 pos, Vector2 direction, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, unsigned long idParent) {
    /**
     * SpawnBullet mais on précise un parent
     */    
    if (nbBullets >= MAX_BULLETS) return; 

    Bullet bullet;
    BulletInit(&bullet, pos, direction, speed, pattern, userData, type, damage, visible, idParent);

}

void SpawnBulletPolParent(Vector2 pos, float angle, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible, unsigned long idParent) {
    /**
     * SpawnBulletPol mais on précise un parent
     */
    Vector2 direction = {cos( PI * angle / 180.f), sin( PI * angle / 180.f)};
    SpawnBulletParent(pos, direction, speed, pattern, userData, type, damage, visible, idParent);
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


