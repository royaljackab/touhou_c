#include "test2.h"

#define bossX objects[bossID].pos.x
#define bossY objects[bossID].pos.y

ObjID bossID;
Object boss;
int timer=0;

int objCount=0;
float angleT=0;

void Initialize() {
    bossID = Obj_Create(OBJ_BOSS);

    //texture du boss
    Obj_SetTexture(bossID, BOSS_SPRITESHEET);
    ObjSprite2D_SetSourceRect(bossID, 16,187,512,84);
    ObjSprite2D_SetAnimation(bossID, 8, 5);
    ObjSprite2D_SetCollisionToShot(bossID, 20);


    ObjMove_SetPosition(bossID, -20, -20);
  
} 

void MainLoop() {
    timer++;

    if(timer==20) {
        ObjMove_SetDestAtSpeed(bossID, 360, 200, 7);
    }

    if(timer > 120 && timer%3==0) {
        int dir=1;
        for(int i=0; i<2; i++) {
            ObjID b = CreateShot(bossX, bossY, 10, 270 + dir * cos(timer/20.0) * 30, BALL_M_BLACK, 0);
            ObjMove_SetForce(b, 0, 0.25);
            ObjMove_AddPattern(b,0,NO_CHANGE,NO_CHANGE,NO_CHANGE,7, 0.1);
            dir *= -1;
        }
    }

    if(timer % 30 == 0 && timer > 120) {
        int nbBull = 50;
        float angleT=0;

        for (int i=0; i<nbBull; i++) {
            ObjID b1 = CreateShot(bossX, bossY, 8, angleT, BALL_M_BLACK, 0);
            ObjSprite2D_SetColor(b1, BLUE);
            ObjMove_SetAccel(b1, -0.4, 0);
            ObjMove_AddPattern(b1, 60, 2, NO_CHANGE, 0.05, 9, -1.5);
            ObjMove_AddPattern(b1, 60, NO_CHANGE, NO_CHANGE, 0.2, 7, 0);


            ObjID b2 = CreateShot(bossX, bossY, 8, angleT, BALL_M_BLACK, 0);
            ObjSprite2D_SetColor(b2, PINK);
            ObjMove_SetAccel(b2, -0.4, 0);
            ObjMove_AddPattern(b2, 60, 2, NO_CHANGE, 0.05, 9, 1.5);
            ObjMove_AddPattern(b2, 60, NO_CHANGE, NO_CHANGE, 0.2, 7, 0);

            angleT += 360.0/nbBull;
        }
    }
    if(timer>=120) {
        objects[bossID].pos.x = cos(timer/50.0) * 100 + 360;
        objects[bossID].pos.y = sin(timer/50.0) * 50 + 200;
    }


}