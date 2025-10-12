#include "globals.h"
#include "bullet.h"

void BulletInit(Bullet* bullet, Vector2 pos, Vector2 direction, float speed, BULLET_PATTERN_FUNC, BulletType type, int damage, int visible) {
    bullet->pos = pos;
    bullet->sprite = bulletSprites[type];
    bullet->speed = speed; 

    bullet->location = (Vector2){pos.x - bullet->sprite.collisionOffset.x, pos.y - bullet->sprite.collisionOffset.y};
    bullet->direction = direction;
    bullet->pattern = pattern;
    bullet->userData = NULL;

    bullet->bActive = TRUE;
    bullet->bDamage = damage;
    bullet->bVisible = visible;

    bullet->timer = 0;

    bullets[nbBullets++] = *bullet;
}

void UpdateBullet(Bullet* bullet) {
    if (!bullet->bActive) return;

    bullet->timer++;
    bullet->location = (Vector2){bullet->pos.x - bullet->sprite.collisionOffset.x, bullet->pos.y - bullet->sprite.collisionOffset.y};

    //Si le bullet est à l'écran, on met à jour son animation
    if ( bullet->pos.x >=0 && bullet->pos.x <= SCREEN_WIDTH && bullet->pos.y >=0 && bullet->pos.y <= SCREEN_HEIGHT && bullet->bVisible) {
        DrawTextureRec(bullet->sprite.spritesheet, bullet->sprite.frameRec, bullet->location, WHITE);
        UpdateAnimation(&bullet->sprite);
    
    //Sinon, si il est trop loin, on le désactive
    } else if (bullet->pos.x < -200 || bullet->pos.x > SCREEN_WIDTH + 200 || bullet->pos.y < -200 || bullet->pos.y > SCREEN_HEIGHT + 200 || !bullet->bVisible) {
        bullet->bActive = FALSE;
    }
}

void UpdateBullets() {
    for (int i = 0; i < nbBullets; i++) {
        UpdateBullet(&bullets[i]);
        bullets[i].pattern(&bullets[i], bullets[i].userData);

        if (!bullets[i].bActive) {
            //On échange avec le dernier et on décrémente
            bullets[i] = bullets[nbBullets - 1];
            nbBullets--;
            i--; //Il faut repasser sur l'index i donc
        }
    }
}

void SpawnBullet(Vector2 pos, Vector2 direction, float speed, BULLET_PATTERN_FUNC, BulletType type, int damage, int visible) {
    if (nbBullets >= MAX_BULLETS) return; 

    Bullet bullet;
    BulletInit(&bullet, pos, direction, speed, pattern, type, damage, visible);

}

void SpawnBulletAngle(Vector2 pos, float angle, float speed, BULLET_PATTERN_FUNC, BulletType type, int damage, int visible) {
    Vector2 direction = {cos( PI * angle / 180.f), sin( PI * angle / 180.f)};
    SpawnBullet(pos, direction, speed, pattern, type, damage, visible);

}

void SpawnBulletCircle(int nbBullets, Vector2 pos, float angle, float speed, BULLET_PATTERN_FUNC, BulletType type, int damage, int visible) {
    for (int i=0; i<nbBullets; i++) {
        SpawnBulletAngle(pos, angle + i * 360 / nbBullets, speed, pattern, type, damage, visible);
    }
}
