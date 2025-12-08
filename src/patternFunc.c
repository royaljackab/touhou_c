#include "globals.h"
#include "patternFunc.h"

void Pattern_Straight(Bullet* bullet, float userData[MAX_DATA]) {
    bullet->pos.x += bullet->direction.x * bullet->speed;
    bullet->pos.y += bullet->direction.y * bullet->speed;
}

void Pattern_SineWave(Bullet* bullet, float userData[MAX_DATA]) {
    bullet->pos.x = 200 * sin(bullet->timer * 1.f / 60) + MIDDLE_SCREEN.x;
    bullet->pos.y = 200 * cos(bullet->timer * 1.f / 60) + MIDDLE_SCREEN.y;
}

void Pattern_SpawnCircle(Bullet* bullet, float userData[MAX_DATA]) {
    /**
     * Cercle qui spawn des cercles qui spawn des cercles...
     * 
     * userData : [nbBullets, speed, circleFrame, generation]
     *  */ 
    Pattern_Straight(bullet, userData);
    float newData[MAX_DATA] = {userData[NB_BULLETS], userData[SPEED] + 1, userData[CIRCLE_FRAME], userData[GENERATION] + 1, userData[GEN_MAX]};

    //SpawnCircleData newData = {data->nbBullets, data->speed, data->circleFrame, data->generation + 1};
    if (bullet->timer == userData[CIRCLE_FRAME] && userData[GENERATION] < userData[GEN_MAX]) {
        SpawnBulletCircle(userData[NB_BULLETS], bullet->pos, 270, userData[SPEED] + 1, Pattern_SpawnCircle, newData, BALL_M_BLACK, 1, 1);   
        bullet->bActive = FALSE; //Detruit le bullet parent
    }
}

void Pattern_Gravity(Bullet* bullet, float userData[MAX_DATA]) {
    /**
     * Bullet soumise à une force de gravité g
     * 
     * userData : [g, x0, y0]
     */

    float g = userData[0];
    float x0 = userData[1];
    float y0 = userData[2];
    Vector2 v0 = Vector2Scale(bullet->direction, bullet->speed);

    bullet->pos.x = v0.x * bullet->timer + x0;
    bullet->pos.y = bullet->timer * (g/2 * bullet->timer + v0.y) + y0;
}   

void Pattern_Test(Bullet* bullet, float userData[MAX_DATA]) {
    if (bullet->timer <= 60) {
        Pattern_Gravity(bullet, userData);
    } else {
        bullet->bActive = 0;
        SpawnBulletToPlayer(bullet->pos, player1, bullet->speed, Pattern_Straight, userData, BALL_M_BLACK, 1, 1);
    }
}