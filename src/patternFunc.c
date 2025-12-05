#include "globals.h"
#include "patternFunc.h"

void Pattern_Straight(Bullet* bullet, int userData[MAX_DATA]) {
    bullet->pos.x += bullet->direction.x * bullet->speed;
    bullet->pos.y += bullet->direction.y * bullet->speed;
}

void Pattern_SineWave(Bullet* bullet, int userData[MAX_DATA]) {
    bullet->pos.x = 200 * sin(bullet->timer * 1.f / 60) + MIDDLE_SCREEN.x;
    bullet->pos.y = 200 * cos(bullet->timer * 1.f / 60) + MIDDLE_SCREEN.y;
}

void Pattern_SpawnCircle(Bullet* bullet, int userData[MAX_DATA]) {
    /**
     * Cercle qui spawn des cercles qui spawn des cercles...
     * 
     * userData : [nbBullets, speed, circleFrame, generation]
     *  */ 
    Pattern_Straight(bullet, userData);
    int newData[MAX_DATA] = {userData[NB_BULLETS], userData[SPEED] + 1, userData[CIRCLE_FRAME], userData[GENERATION] + 1, userData[GEN_MAX]};

    //SpawnCircleData newData = {data->nbBullets, data->speed, data->circleFrame, data->generation + 1};
    if (bullet->timer == userData[CIRCLE_FRAME] && userData[GENERATION] < userData[GEN_MAX]) {
        SpawnBulletCircle(userData[NB_BULLETS], bullet->pos, 270, userData[SPEED] + 1, Pattern_SpawnCircle, newData, BALL_M_BLACK, 1, 1);   
        bullet->bActive = FALSE; //Detruit le bullet parent
    }
}