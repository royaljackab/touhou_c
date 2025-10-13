#include "include/raylib.h"
#include <stdio.h>
#include "globals.h"

Assets assets;
Sprite bulletSprites[MAX_SPRITES];
Bullet bullets[MAX_BULLETS];
int nbBullets = 0;
int frame=0;

void init() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Touhou");
    SetTargetFPS(60);

    LoadAllAssets();
    LoadBulletSprites();
}

void pattern_test_circleSpawn() {
    int data[MAX_DATA] = {10, 2, 60, 0, 2}; //nbBullets, speed, circleFrame, generation, genMax
    if (frame%360 == 0) {
        SpawnBulletCircle(12, MIDDLE_BOSS, 270, 2, Pattern_SpawnCircle, data, BALL_M_BLACK, 1,1);
    }
}



int main() {
    init();

    char str[20];

    while(!WindowShouldClose()) {

        pattern_test_circleSpawn();

        sprintf(str, "%d", nbBullets);

        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(str, 10 ,10, 20, WHITE);
            DrawFPS(40,40);

            UpdateBullets();
        EndDrawing();

        frame++;
    }
    CloseWindow();
}