#include "include/raylib.h"
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

void pattern_test() {
    if (frame%360 == 0) {
        SpawnBulletCircle(12, MIDDLE_SCREEN, 270, 2, Pattern_SpawnCircle, BALL_M_BLACK, 1);
    }
}



int main() {
    init();

    while(!WindowShouldClose()) {

        pattern_test();

        BeginDrawing();
            ClearBackground(BLACK);

            UpdateBullets();
        EndDrawing();

        frame++;
    }
    CloseWindow();
}