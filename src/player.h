#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include "globals.h"

typedef struct {
    Sprite sprite;

    Vector2 pos;
    float speed;
    float focusSpeed;

    int nbLife;
    int life;
    int nbBombs;
    int bomb;

    int playerType;
} Player;

enum {
    REIMU_A,
    REIMU_B,
    MARISA_A,
    MARISA_B
};

enum {
    REIMU,
    MARISA
};

extern Player player;
extern Sprite playerSprites[2];
extern Player characters[4];

void Load_PlayerSprites();
void Load_Players();
void InitPlayer(int playerType);
void UpdatePlayer();
void DrawPlayer();
void UpdateAnimationPlayer();

#endif
