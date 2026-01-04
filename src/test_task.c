#include "task.h"
#include "test_task.h"

#define bossX objects[bossID].pos.x
#define bossY objects[bossID].pos.y

ObjID bossID;

void initialize() {
    bossID = Obj_Create(OBJ_BOSS);

    //texture du boss
    Obj_SetTexture(bossID, BOSS_SPRITESHEET);
    ObjSprite2D_SetSourceRect(bossID, 16,187,512,84);
    ObjSprite2D_SetAnimation(bossID, 8, 5);
    ObjSprite2D_SetCollisionToShot(bossID, 20);


    ObjMove_SetPosition(bossID, -20, -20);
} 


static void fireRing(Task_contParam) {
    Task_beginContext;
        int i;
    Task_endContext(ctx);

    Task_begin(ctx);

    float angleT = GetRandomValue(0,360);
    for (ctx->i = 0; ctx->i < 48; ctx->i++) {
        CreateShot(bossX,bossY, 4.5, angleT, BALL_M_BLACK, 0);
        angleT += 360.0/48;
    }

    Task_finishV;
}

static void fireLaser(Task_contParam, int dir) {
    Task_beginContext;
    Task_endContext(ctx);

    Task_begin(ctx);

    ObjID obj = CreateLaser(bossX,bossY,180 + 105*dir,1000,15,120, RED_LASER, 30);
    ObjMove_AddPattern(obj, 30, NO_CHANGE, NO_CHANGE, NO_CHANGE, NO_CHANGE, 0.5 * dir);

    Task_finishV;
}

static void movement(Task_contParam) {
    Task_beginContext;
    Task_endContext(move);

    Task_begin(move);

    while(objects[bossID].active == true) {
        ObjMove_SetDestAtFrame(bossID, GetRandomValue( 30, 500), 200 + GetRandomValue(-20,50), 60);
        wait(move, 360);
    }

    Task_finishV;
}

void moonlight_task(Task_contParam) {
    Task_beginContext;
        int count;
        void *ringState;
        void *moveState;
        void *laserState;
    Task_endContext(moon);
    
    Task_begin(moon);

    if (moon->Task_line == 0) {moon->ringState = NULL; moon->moveState = NULL; moon->laserState = NULL;}
    moon->count = 0;
    ObjMove_SetDestAtFrame(bossID, 300, 200, 60);
    wait(moon, 80);

    while(1) {

        if (moon->count == 0) {
            movement(&moon->moveState);
        }
        if(moon->count % 10 == 0) {
            fireRing(&moon->ringState);
        }
        if(moon->count % 360 == 90) {
            fireLaser(&moon->laserState, 1);
            fireLaser(&moon->laserState, -1);
        }

        moon->count++;
        yield;
    }

    Task_finishV;
}

