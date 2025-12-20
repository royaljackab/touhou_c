#include "obj.h"

Object objects[MAX_OBJECTS];



ObjID Obj_Create(ObjType type) {
    for (int i=0; i<MAX_OBJECTS; i++) {
        if(!objects[i].active) {
            objects[i].active = true;
            objects[i].type = type;
            objects[i].speed = 0;
            objects[i].sprite.color = WHITE;
            objects[i].maxLife = 100;
            objects[i].life = 100;
            objects[i].timer = 0;
            objects[i].delay = 0;
            objects[i].accel = 0;
            objects[i].angVel = 0;
            objects[i].maxSpd = NO_LIMIT;
            objects[i].patternCount = 0;
            objects[i].force = (Vector2){0,0};
            return i; //i devient ObjID
        }
    }
    
    //Aucune place disponible
    return ID_INVALID;
}

static void ShiftPatterns(Object* obj) {
    for (int i=0; i < obj->patternCount - 1; i++) {
        obj->patterns[i] = obj->patterns[i+1];
    }
    obj->patternCount--;
}

static void ApplyMoveParams(Object* obj, MovePattern* p) {
    if (p->speed != NO_CHANGE) obj->speed = p->speed;
    if (p->angle != NO_CHANGE) obj->angle = p->angle;
    if (p->accel != NO_CHANGE) obj->accel = p->accel;
    if (p->angVel != NO_CHANGE) obj->angVel = p->angVel;
    if (p->maxSpd != NO_CHANGE) obj->maxSpd = p->maxSpd;
}

void ObjMove_AddPattern(ObjID id, int frameDelay, float speed, float angle, float accel, float maxSpd, float angVel) {
    if (id==ID_INVALID) return;
    if (objects[id].patternCount >= MAX_PATTERNS) return;

    int i = objects[id].patternCount;
    objects[id].patterns[i].delay = frameDelay;
    objects[id].patterns[i].speed = speed;
    objects[id].patterns[i].angle = angle;
    objects[id].patterns[i].maxSpd = maxSpd;
    objects[id].patterns[i].accel = accel;
    objects[id].patterns[i].angVel = angVel;

    objects[id].patternCount++;
}

void Obj_Delete(ObjID* id) {
    if(*id==ID_INVALID) return;
    objects[*id].active=false;
    *id = ID_INVALID;
}

void Obj_SetDelay(ObjID id, int delay) {
    if(id==ID_INVALID) return;
    objects[id].delay = delay;
}

void ObjMove_SetPosition(ObjID id, float x, float y) {
    if(id==ID_INVALID) return;
    objects[id].pos = (Vector2){x,y};
}

void ObjMove_SetSpeed(ObjID id, float speed) {
    if(id == ID_INVALID) return;
    objects[id].speed = speed;
}

void ObjMove_SetAngle(ObjID id, float angle) {
    if(id == ID_INVALID) return;
    objects[id].angle = angle;
}

void ObjMove_SetAccel(ObjID id, float acc, float maxSpd) {
    if(id==ID_INVALID) return;
    objects[id].accel = acc;
    objects[id].maxSpd = maxSpd;
}

void ObjMove_SetDestAtSpeed(ObjID id, float x, float y, float speed) {
    if(id==ID_INVALID) return;
    objects[id].movingToDest = true;
    objects[id].destPos = (Vector2){x,y};

    objects[id].speed = speed;
    objects[id].angle = atanf((y - objects[id].pos.y)/(x - objects[id].pos.x)) * (180.0f/PI);
}

void ObjMove_SetForce(ObjID id, float x, float y) {
    if(id==ID_INVALID) return;
    objects[id].force = (Vector2){x,y};
}

void ObjLaser_SetLength(ObjID id, float length) {
    if(id==ID_INVALID) return;
    objects[id].laserLength = length;
}

void ObjLaser_SetMaxWidth(ObjID id, float maxWidth) {
    if(id==ID_INVALID) return;
    objects[id].laserMaxWidth = maxWidth;
}

void ObjLaser_SetTimers(ObjID id, int warning, int growing, int duration) {
    if(id==ID_INVALID) return;
    if (warning != NO_CHANGE) objects[id].warningTimer = warning;
    if (growing != NO_CHANGE) objects[id].growingTimer = growing;
    if (duration != NO_CHANGE) objects[id].laserDuration = duration;
}

void ObjLaser_SetIntersectionWidth(ObjID id, int intersectionWidth) {
    if(id==ID_INVALID) return;
    objects[id].intersectionWidth = intersectionWidth;
}

void ObjLaser_SetInvalidLength(ObjID id, int ratioBase, int ratioTip) {
    if(id==ID_INVALID) return;
    objects[id].invalidLengthBase = ratioBase;
    objects[id].invalidLengthTip = ratioTip;
}   

void ObjLaser_SetGrowingTime(ObjID id, int growing) {
    ObjLaser_SetTimers(id, NO_CHANGE, growing, NO_CHANGE);
}

void ObjEnemy_SetLife(ObjID id, float hp) {
    if(id==ID_INVALID) return;
    objects[id].maxLife = hp;
    objects[id].life = hp;
}

void ObjEnemy_AddLife(ObjID id, float hp) {
    if(id==ID_INVALID) return;
    objects[id].life -= hp;
}

void UpdateObjects() {
    for (int i=0; i<MAX_OBJECTS; i++) {
        if(!objects[i].active) continue;

        if(objects[i].pos.x < PANEL_LEFT - DRAW_MARGIN || objects[i].pos.x > PANEL_LEFT + PANEL_WIDTH + DRAW_MARGIN 
            || objects[i].pos.y < PANEL_UP - DRAW_MARGIN || objects[i].pos.y > PANEL_UP + PANEL_HEIGHT + DRAW_MARGIN || objects[i].life <= 0) { 
            
            objects[i].active=false;
        }
        
        objects[i].timer++;

        if(objects[i].movingToDest) {
            float distRemaining = Vector2Distance(objects[i].pos, objects[i].destPos);

            if (distRemaining <= objects[i].speed) {
                objects[i].pos = objects[i].destPos;
                objects[i].speed = 0;
                objects[i].movingToDest = false;
                continue;
            }
        }

        //Gestion patterns
        if(objects[i].patternCount > 0) {
            MovePattern* currPat = objects[i].patterns;
            currPat->delay--;

            if (currPat->delay <= 0) {
                ApplyMoveParams(&objects[i], currPat);
                ShiftPatterns(&objects[i]);

            }
        }

        //Physique
        objects[i].angle += objects[i].angVel;

        //Acceleration
        if (objects[i].accel != 0) {
            objects[i].speed += objects[i].accel;
        }
        if (objects[i].maxSpd != NO_LIMIT) {
            if(objects[i].accel > 0 && objects[i].speed > objects[i].maxSpd) objects[i].speed = objects[i].maxSpd;
            else if(objects[i].accel < 0 && objects[i].speed < objects[i].maxSpd) objects[i].speed = objects[i].maxSpd;
        }

        //Force
        if(objects[i].force.x != 0 || objects[i].force.y != 0) {
            float rad = objects[i].angle * DEG2RAD;

            float vx = cosf(rad) * objects[i].speed;
            float vy = sinf(rad) * objects[i].speed;

            vx += objects[i].force.x;
            vy += objects[i].force.y;

            objects[i].speed = sqrtf(vx*vx + vy*vy);
            objects[i].angle = atan2f(vy,vx) * RAD2DEG;
        }

        //Direction
        float rad = objects[i].angle * DEG2RAD;
        Vector2 velocity = Vector2Scale((Vector2){cosf(rad), sinf(rad)}, objects[i].speed);
        objects[i].pos = Vector2Add(objects[i].pos, velocity);

        if(objects[i].type == OBJ_ENEMY_LASER || objects[i].type == OBJ_PLAYER_LASER) {
            int warning = objects[i].warningTimer;
            int growing = objects[i].growingTimer;
            int duration = objects[i].laserDuration;

            if(objects[i].timer < warning) {
                objects[i].laserWidth = 2;
                objects[i].laserState = 0;
            }
            else if(objects[i].timer < growing + warning) {
                objects[i].laserWidth += objects[i].laserMaxWidth / objects[i].growingTimer;
                objects[i].laserState = 1;
            }
            else if(objects[i].timer < growing + warning + duration) {
                objects[i].laserWidth = objects[i].laserMaxWidth;
                objects[i].laserState = 1;
            }
            else {
                objects[i].laserWidth -= objects[i].laserMaxWidth / objects[i].growingTimer;
                if(objects[i].laserWidth <= 0) objects[i].active = false;
            }
        }
    }
}

void Obj_SetTexture(ObjID id, int textureID) {
    if(id == ID_INVALID) return;
    SetTexture(&objects[id].sprite, textureID);
}

void ObjSprite2D_SetSourceRect(ObjID id, float x, float y, float width, float height) {
    if(id==ID_INVALID) return;
    SetSourceRect(&objects[id].sprite, x, y, width, height);
}

void ObjSprite2D_SetCenter(ObjID id, float x, float y) {
    if(id==ID_INVALID) return;
    SetCenter(&objects[id].sprite, x,y);
}

void ObjSprite2D_SetRotation(ObjID id, float rotation) {
    if(id==ID_INVALID) return;
    SetRotation(&objects[id].sprite, rotation);
}

void ObjSprite2D_SetScale(ObjID id, float x, float y) {
    if(id==ID_INVALID) return;
    SetScale(&objects[id].sprite,x,y);
}

void ObjSprite2D_SetColor(ObjID id, Color color) {
    if(id==ID_INVALID) return;
    SetColor(&objects[id].sprite, color);
}

void ObjSprite2D_SetAnimation(ObjID id, int frameCount, int delay) {
    if(id==ID_INVALID) return;
    SetAnimation(&objects[id].sprite, frameCount, delay);
}

void ObjSprite2D_SetCollisionToShot(ObjID id, float radius) {
    if(id==ID_INVALID) return;
    SetCollisionRadius(&objects[id].sprite, radius);
}

void UpdateAnimations() {
    for(int i=0; i<MAX_OBJECTS; i++) {
        if (objects[i].active && objects[i].sprite.isAnimated) {
            UpdateAnimation(&objects[i].sprite);
        }
    }
}

void DrawObjects() {
    for(int i=0; i<MAX_OBJECTS; i++) {
        if(objects[i].active && objects[i].timer >= objects[i].delay && objects[i].pos.x >= PANEL_LEFT && objects[i].pos.x <= PANEL_LEFT + PANEL_WIDTH 
            && objects[i].pos.y >= PANEL_UP && objects[i].pos.y <= PANEL_UP + PANEL_HEIGHT) {
            DrawSprite(objects[i].sprite, objects[i].pos);
        }
    }
}

void UpdateCollisions() {
    for(int j=0; j<MAX_OBJECTS; j++) {

        if(!objects[j].active || (objects[j].type != OBJ_ENEMY  && objects[j].type != OBJ_BOSS)) continue;
    
        for(int i=0; i<MAX_OBJECTS; i++) {

            if(!objects[i].active || objects[i].type != OBJ_PLAYER_SHOT) continue;

            if (CheckCollisionCircles(objects[j].sprite.center, objects[j].sprite.hitboxRadius, objects[i].sprite.center, objects[i].sprite.hitboxRadius)) {
                ObjEnemy_AddLife(j, objects[i].damage);
                objects[i].active=false;
            }
        }
    }
}


