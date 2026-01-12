#include "bullet_shot.h"

ObjID CreateShotType(ObjType type, float x, float y, float speed, float angle, BulletGraphic graphic, int delay) {
    int id = Obj_Create(type);

    ObjMove_SetPosition(id, x, y);
    ObjMove_SetSpeed(id, speed);
    ObjMove_SetAngle(id, angle);

    ObjSprite2D_SetBulletSprite(id, graphic);

    Obj_SetDelay(id, delay);

    return id;
}


ObjID CreateShot(float x, float y, float speed, float angle, BulletGraphic graphic, int delay) {
    return CreateShotType(OBJ_ENEMY_SHOT, x, y, speed, angle, graphic, delay);
}

ObjID CreateLaser(float x, float y, float angle, float length, float maxWidth, int deleteTime, BulletGraphic graphic, int delay) {
    int id = Obj_Create(OBJ_ENEMY_LASER);

    ObjMove_SetPosition(id, x, y);
    ObjMove_SetAngle(id, angle);
    
    ObjLaser_SetLength(id, length);
    ObjLaser_SetMaxWidth(id, maxWidth);
    ObjLaser_SetTimers(id, delay, 10, deleteTime);

    ObjSprite2D_SetBulletSprite(id, graphic);

    objects[id].laserWidth=0;
    objects[id].laserState=0;

    return id;
}