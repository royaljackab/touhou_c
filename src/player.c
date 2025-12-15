#include "player.h"

Player player;

Sprite playerSprites[2];
Player characters[4];

void Load_PlayerSprites() {
    SetTexture(&playerSprites[REIMU], REIMU_IDLE);
    SetSourceRect(&playerSprites[REIMU], 0,0,256,48);
    SetAnimation(&playerSprites[REIMU], 8, 3);
    SetCollisionRadius(&playerSprites[REIMU], 5);
}

void Load_Players() {
    characters[REIMU_A] = (Player){
        playerSprites[REIMU],
        (Vector2){300,800},
        7,
        5,
        3,
        3,
        3,
        3,
        REIMU_A
    };
}

void InitPlayer(int playerType) {
    player = characters[playerType];
}

void UpdatePlayer() {

    float speed = player.speed;
    if(IsKeyDown(KEY_LEFT_SHIFT)) {
        speed = player.focusSpeed;
    }

    Vector2 move = {0,0};

    if(IsKeyDown(KEY_LEFT)) move = Vector2Add(move, (Vector2){-1,0});
    if(IsKeyDown(KEY_UP)) move = Vector2Add(move, (Vector2){0,-1});
    if(IsKeyDown(KEY_RIGHT)) move = Vector2Add(move, (Vector2){1,0});
    if(IsKeyDown(KEY_DOWN)) move = Vector2Add(move, (Vector2){0,1});

    move = Vector2Normalize(move);
    player.pos = Vector2Add(player.pos, Vector2Scale(move, speed));
    player.pos.x = Clamp(player.pos.x, PANEL_LEFT, PANEL_LEFT + PANEL_WIDTH);
    player.pos.y = Clamp(player.pos.y, PANEL_UP, PANEL_UP + PANEL_HEIGHT);
}

void DrawPlayer() {
    DrawSprite(player.sprite, player.pos);
}

void UpdateAnimationPlayer() {
    UpdateAnimation(&player.sprite);
}