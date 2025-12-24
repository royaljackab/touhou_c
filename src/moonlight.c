#include "moonlight.h"

#define bossX objects[bossID].pos.x
#define bossY objects[bossID].pos.y

static ObjID bossID;
static int timer=0;

void fireRing() {
    float angleT = GetRandomValue(0,360);
    for(int i=0; i<48; i++) {
        CreateShot(bossX, bossY, 4.5, angleT, BALL_M_BLACK, 0);
        angleT += 360.0/48;
    }
}

void fireLaser(int dir) {
    ObjID obj = CreateLaser(bossX,bossY,180 + 105*dir,1000,15,120, RED_LASER, 30);
    ObjMove_AddPattern(obj, 30, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, 0.5 * dir);
}

void moonlight_init() {
    bossID = Obj_Create(OBJ_BOSS);

    //texture du boss
    Obj_SetTexture(bossID, BOSS_SPRITESHEET);
    ObjSprite2D_SetSourceRect(bossID, 16,187,512,84);
    ObjSprite2D_SetAnimation(bossID, 8, 5);
    ObjSprite2D_SetCollisionToShot(bossID, 20);


    ObjMove_SetPosition(bossID, 360, 200);
}

void moonlight() {
    if (timer % 360 == 0) {
        ObjMove_SetDestAtFrame(bossID, GetRandomValue( 30, 500), 200 + GetRandomValue(-20,50), 60);
    }
    if (timer > 60 && timer % 30 == 0) {
        fireRing();
    }
    if (timer > 60 && timer % 360 == 90) {
        fireLaser(1); fireLaser(-1);
    }

    timer++;

}



