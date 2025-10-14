#ifndef PLAYER_H
#define PLAYER_H

#include "include/raylib.h"
#include "include/raymath.h"
#include "assets.h"
#include "sprite.h"
#include "globals.h"

#define INVINSIBILITY_DURATION 10

typedef struct {
  Vector2 location; //Corner Up-Left for drawing
  Vector2 pos; //Center for collision
  float speed; 
  float focusSpeed;
  int hp;
  int nbBombs;

  Sprite sprite;
  int invisFrames; //nombre de frames d'invinsibilité avant que le joueur ne puisse prendre des dégâts

} Player;

void PlayerInit(Player *p, Vector2 pos, float speed, float focusSpeed, int hp, Sprite sprite);
void UpdatePlayer(Player *p);
//int damagePlayer(Player *p, int damage); 

#endif