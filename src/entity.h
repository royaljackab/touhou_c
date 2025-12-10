#ifndef ENTITY_H
#define ENTITY_H

#define ENTITY_PATTERN_FUNC void (*pattern)(struct entityTemp* entity, float userData[MAX_DATA])

#include "include/raylib.h"
#include "assets.h"
#include "sprite.h"


#define MAX_DATA 10

typedef struct entityTemp {
    Sprite sprite;

    Vector2 pos; //Center
    Vector2 location; //Corner Up-Left for drawing
    Vector2 direction;
    float speed;

    int timer;
    void (*pattern)(struct entityTemp* entity, float userData[MAX_DATA]);
    float userData[MAX_DATA];

    int bActive;
    int bVisible;
    int bDamage;
} Entity;

void EntityInit(Entity* entity, Vector2 pos, Vector2 direction, float speed, ENTITY_PATTERN_FUNC, float userData[MAX_DATA], BulletType type, int damage, int visible);
void UpdateEntity(Entity* entity);
void ShowEntityHitbox(Entity* entity);
void Rotate_Entity(Entity* entity, float angle);

#endif