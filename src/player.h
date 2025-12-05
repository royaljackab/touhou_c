#ifndef PLAYER_H
#define PLAYER_H

#include "include/raylib.h"
#include "include/raymath.h"
#include "assets.h"
#include "sprite.h"
#include "globals.h"

#define INVINSIBILITY_DURATION 100

typedef struct {
  Vector2 location; //Coin en haut a gauche pour affichage du sprite
  Vector2 pos; //Centre pour la collision
  float speed; 
  float focusSpeed;
  int hp;
  int nbBombs;

  Sprite sprite;
  int invisFrames; //nombre de frames d'invinsibilité avant que le joueur ne puisse prendre des dégâts

} Player;

void PlayerInit(Player *p, Vector2 pos, float speed, float focusSpeed, int hp, Sprite sprite);
void UpdatePlayer(Player *p);
int playerIsColliding(Player *p);
int damagePlayer(Player *p, int damage); 
void showHitbox(Player *p);

#endif