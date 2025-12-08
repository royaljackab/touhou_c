#include "globals.h"

Assets assets;
Sprite bulletSprites[MAX_SPRITES];
Bullet bullets[MAX_BULLETS];
Bullet enemies[MAX_ENEMIES];
int nbBullets = 0;
int nbEnemies = 0;
int frame = 0;

//Debug mode : Affiche les hitbox
int debug=0;

Player player1;

void init() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Touhou");
    SetTargetFPS(60);

    LoadAllAssets();
    LoadBulletSprites();

    //Player, pos, speed, focusSpeed, HP, Sprite
    PlayerInit(&player1, (Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT - 100}, 8, 4, 5, bulletSprites[REIMU_STILL]);
}

void pattern_test_circleSpawn() {
    float data[MAX_DATA] = {0.01, MIDDLE_BOSS.x, MIDDLE_BOSS.y};
    float angleRand;
    if (frame%30==0) {
        angleRand = GetRandomValue(0,360);
        SpawnBulletCircle(12, MIDDLE_BOSS, angleRand, 5, Pattern_Test, data, BALL_M_BLACK, 1, 1);
        SpawnEnemyPol(MIDDLE_BOSS, angleRand, 5, Pattern_Straight, data, FAIRY_S_BLUE_STILL, 1, 1, 50);
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

            
            UpdatePlayer(&player1);
            UpdateBullets();
            UpdateEnemies();
        EndDrawing();

        frame++;
    }
    CloseWindow();
}
