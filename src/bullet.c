#include "globals.h"
#include "bullet.h"


void BulletInit(Bullet* bullet, Vector2 pos, Vector2 direction, float speed, BULLET_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible) {
    bullet->pos = pos;
    bullet->sprite = bulletSprites[type];
    bullet->speed = speed; 

    bullet->location = (Vector2){pos.x - bullet->sprite.collisionOffset.x, pos.y - bullet->sprite.collisionOffset.y};
    bullet->direction = Vector2Normalize(direction);
    bullet->pattern = pattern;
    memcpy(bullet->userData, userData, sizeof(float)*MAX_DATA);

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
    if ( bullet->pos.x >=PANEL_WIDTH && bullet->pos.x <= SCREEN_WIDTH - PANEL_WIDTH && bullet->pos.y >= 0 && bullet->pos.y <= SCREEN_HEIGHT && bullet->bVisible) {
        DrawTextureRec(bullet->sprite.spritesheet, bullet->sprite.frameRec, bullet->location, WHITE);
        UpdateAnimation(&bullet->sprite);
        if (debug==1) ShowBulletHitbox(bullet);

    //Sinon, si il est trop loin, on le désactive
    } else if (bullet->pos.x < PANEL_WIDTH - 200 || bullet->pos.x > SCREEN_WIDTH - PANEL_WIDTH + 200 || bullet->pos.y < PANEL_WIDTH - 200 || bullet->pos.y > SCREEN_HEIGHT - PANEL_WIDTH + 200 || !bullet->bVisible) {
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

void Rotate_Bullet(Bullet* bullet, float angle){
    /**
     * Effectue une rotation sur la direction d'une balle selon un angle
     */
    bullet->direction = Vector2Rotate(bullet->direction, angle);
}


void ShowBulletHitbox(Bullet* bullet) {
    /**
     * Affiche les hitbox de chaque balle par un cercle bleu (debug mode)
     */
    DrawCircleV(bullet->pos, bullet->sprite.collisionRadius, BLUE);
}

void SpawnBullet(Vector2 pos, Vector2 direction, float speed, BULLET_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible) {
    if (nbBullets >= MAX_BULLETS) return; 

    Bullet bullet;
    BulletInit(&bullet, pos, direction, speed, pattern, userData, type, damage, visible);

}

void SpawnBulletPol(Vector2 pos, float angle, float speed, BULLET_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible) {
    /**
     * Spawn Bullet mais coordonnées polaires
     */
    Vector2 direction = {cos( PI * angle / 180.f), sin( PI * angle / 180.f)};
    SpawnBullet(pos, direction, speed, pattern, userData, type, damage, visible);
}


void SpawnBulletCircle(int nbBullets, Vector2 pos, float angle, float speed, BULLET_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible) {
    for (int i=0; i<nbBullets; i++) {
        SpawnBulletPol(pos, angle + i * 360 / nbBullets, speed, pattern, userData, type, damage, visible);
    }
}

void SpawnBulletToPlayer(Vector2 pos, Player player, float speed, BULLET_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible) {
    Vector2 srcToPlayer = Vector2Subtract(player.pos, pos);

    SpawnBullet(pos, srcToPlayer, 5, pattern, userData, type, damage, visible);
}


