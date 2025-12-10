#include "globals.h"
#include "patternFunc.h"

void Pattern_Straight(Entity* entity, float userData[MAX_DATA]) {
    entity->pos.x += entity->direction.x * entity->speed;
    entity->pos.y += entity->direction.y * entity->speed;
}

// void Pattern_SineWave(Entity* entity, float userData[MAX_DATA]) {
//     entity->pos.x = 200 * sin(entity->timer * 1.f / 60) + MIDDLE_SCREEN.x;
//     entity->pos.y = 200 * cos(entity->timer * 1.f / 60) + MIDDLE_SCREEN.y;
// }

void Pattern_SineWave(Entity* entity, float userData[MAX_DATA]) {
    Pattern_Straight(entity, userData);

}

void Pattern_SpawnCircle(Entity* entity, float userData[MAX_DATA]) {
    /**
     * Cercle qui spawn des cercles qui spawn des cercles...
     * 
     * userData : [nbBullets, speed, circleFrame, generation]
     *  */ 
    Pattern_Straight(entity, userData);
    float newData[MAX_DATA] = {userData[NB_BULLETS], userData[SPEED] + 1, userData[CIRCLE_FRAME], userData[GENERATION] + 1, userData[GEN_MAX]};

    //SpawnCircleData newData = {data->nbBullets, data->speed, data->circleFrame, data->generation + 1};
    if (entity->timer == userData[CIRCLE_FRAME] && userData[GENERATION] < userData[GEN_MAX]) {
        SpawnBulletCircle(userData[NB_BULLETS], entity->pos, 270, userData[SPEED] + 1, Pattern_SpawnCircle, newData, BALL_M_BLACK, 1, 1);   
        entity->bActive = FALSE; //Detruit entity ""parent""
    }
}

void Pattern_Gravity(Entity* entity, float userData[MAX_DATA]) {
    /**
     * Entity soumise à une force de gravité g
     * 
     * userData : [g, x0, y0]
     */

    float g = userData[0];
    float x0 = userData[1];
    float y0 = userData[2];
    Vector2 v0 = Vector2Scale(entity->direction, entity->speed);

    entity->pos.x = v0.x * entity->timer + x0;
    entity->pos.y = entity->timer * (g/2 * entity->timer + v0.y) + y0;
}   

void Pattern_Test(Entity* entity, float userData[MAX_DATA]) {
    if (entity->timer <= 60) {
        Pattern_Gravity(entity, userData);
    } else {
        entity->bActive = 0;
        SpawnBulletToPlayer(entity->pos, player1, entity->speed, Pattern_Straight, userData, BALL_M_BLACK, 1, 1);
    }
}