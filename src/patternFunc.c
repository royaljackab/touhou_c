#include "globals.h"
#include "patternFunc.h"

void Pattern_Straight(Bullet* bullet, int userData[MAX_DATA]) {
    bullet->pos.x += bullet->direction.x * bullet->speed;
    bullet->pos.y += bullet->direction.y * bullet->speed;
}

void Pattern_SineWave(Bullet* bullet, int userData[MAX_DATA]) {
    bullet->pos.x = 500 * sin(bullet->timer * 1.f / 60) + MIDDLE_SCREEN.x;
    bullet->pos.y = 600 * cos(bullet->timer * 1.f / 60) + MIDDLE_SCREEN.y;
}

void Pattern_SpawnCircle(Bullet* bullet, int userData[MAX_DATA]) {
    // userData : [nbBullets, speed, circleFrame, generation]
    Pattern_Straight(bullet, userData);
    int newData[MAX_DATA] = {userData[NB_BULLETS], userData[SPEED], userData[CIRCLE_FRAME], userData[GENERATION] + 1};

    //SpawnCircleData newData = {data->nbBullets, data->speed, data->circleFrame, data->generation + 1};
    if (bullet->timer % userData[CIRCLE_FRAME] == 0 && userData[GENERATION] < 2) {
        SpawnBulletCircle(userData[NB_BULLETS], bullet->pos, 270, userData[SPEED], Pattern_SpawnCircle, newData, BALL_M_BLACK, 1, 1);   
    }
}