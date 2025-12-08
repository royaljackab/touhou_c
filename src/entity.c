#include "globals.h"
#include "entity.h"

void EntityInit(Entity* entity, Vector2 pos, Vector2 direction, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible) {
    entity->pos = pos;
    entity->sprite = bulletSprites[type];
    entity->speed = speed; 

    entity->location = (Vector2){pos.x - entity->sprite.collisionOffset.x, pos.y - entity->sprite.collisionOffset.y};
    entity->direction = Vector2Normalize(direction);
    entity->pattern = pattern;
    memcpy(entity->userData, userData, sizeof(float)*MAX_DATA);

    entity->bActive = TRUE;
    entity->bDamage = damage;
    entity->bVisible = visible;
    entity->timer = 0;
}

void UpdateEntity(Entity* entity) {
    if (!entity->bActive) return;

    entity->timer++;
    entity->location = (Vector2){entity->pos.x - entity->sprite.collisionOffset.x, entity->pos.y - entity->sprite.collisionOffset.y};

    //Si le entity est à l'écran, on met à jour son animation
    if ( entity->pos.x >=PANEL_WIDTH && entity->pos.x <= SCREEN_WIDTH - PANEL_WIDTH && entity->pos.y >= 0 && entity->pos.y <= SCREEN_HEIGHT && entity->bVisible) {
        DrawTextureRec(entity->sprite.spritesheet, entity->sprite.frameRec, entity->location, WHITE);
        UpdateAnimation(&entity->sprite);
        if (debug==1) ShowEntityHitbox(entity);

    //Sinon, si il est trop loin, on le désactive
    } else if (entity->pos.x < PANEL_WIDTH - 200 || entity->pos.x > SCREEN_WIDTH - PANEL_WIDTH + 200 || entity->pos.y < PANEL_WIDTH - 200 || entity->pos.y > SCREEN_HEIGHT - PANEL_WIDTH + 200 || !entity->bVisible) {
        entity->bActive = FALSE;
    }
}

void RotateEntity(Entity* entity, float angle){
    /**
     * Effectue une rotation sur la direction d'une balle selon un angle
     */
    entity->direction = Vector2Rotate(entity->direction, angle);
}


void ShowEntityHitbox(Entity* entity) {
    /**
     * Affiche les hitbox de chaque balle par un cercle bleu (debug mode)
     */
    DrawCircleV(entity->pos, entity->sprite.collisionRadius, BLUE);
}