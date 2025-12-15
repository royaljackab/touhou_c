#include "bullet_shot.h"

ObjID CreateShot(float x, float y, float speed, float angle, BulletGraphic graphic, int delay) {
    int id = Obj_Create(OBJ_ENEMY_SHOT);

    ObjMove_SetPosition(id, x, y);
    ObjMove_SetSpeed(id, speed);
    ObjMove_SetAngle(id, angle);

    ObjSprite2D_SetBulletSprite(id, graphic);

    Obj_SetDelay(id, delay);

    return id;
}