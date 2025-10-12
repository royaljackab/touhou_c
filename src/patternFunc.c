#include "globals.h"
#include "patternFunc.h"

void Pattern_Straight(Bullet* bullet, void* userData) {
    bullet->pos.x += bullet->direction.x * bullet->speed;
    bullet->pos.y += bullet->direction.y * bullet->speed;
}

void Pattern_SineWave(Bullet* bullet, void* userData) {
    bullet->pos.x = 500 * sin(bullet->timer * 1.f / 60) + MIDDLE_SCREEN.x;
    bullet->pos.y = 600 * cos(bullet->timer * 1.f / 60) + MIDDLE_SCREEN.y;
}

void Pattern_SpawnCircle(Bullet* bullet, void* userData) {
    Pattern_Straight(bullet, userData);
    if (bullet->timer % 100 == 0) {
        SpawnBulletCircle(12, bullet->pos, 270, 3, Pattern_SpawnCircle, NULL, BALL_M_BLACK, 1, 1);   
    }
}