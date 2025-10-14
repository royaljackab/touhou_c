#include "player.h"

void PlayerInit(Player *p, Vector2 pos, float speed, float focusSpeed, int hp, Sprite sprite){
  p->pos = pos;
  p->location = (Vector2){pos.x - sprite.collisionOffset.x, pos.y - sprite.collisionOffset.y};

  p->speed = speed;
  p->focusSpeed = focusSpeed;

  p->hp = hp;
  p->nbBombs = 3;

  p->sprite = sprite;
  p->invisFrames = INVINSIBILITY_DURATION;
}

void UpdatePlayer(Player *p){
  //Met à jour la position du joueur en fonction de sa position centrale
  p->location = (Vector2){p->pos.x - p->sprite.collisionOffset.x, p->pos.y - p->sprite.collisionOffset.y};

  float speed;
  //Si en focus ou pas
  if(IsKeyDown(KEY_LEFT_SHIFT)) {
    speed = p->focusSpeed;
  } else {
    speed = p->speed;
  }
  //Bouge le joueur
  if(IsKeyDown(KEY_RIGHT)) {
    p->pos.x = MoveWithinGameX(p->pos.x + speed);
  }
  if(IsKeyDown(KEY_LEFT)) {
    p->pos.x = MoveWithinGameX(p->pos.x - speed);
  }
  if(IsKeyDown(KEY_UP)) {
    p->pos.y = MoveWithinGameY(p->pos.y - speed);
  }
  if(IsKeyDown(KEY_DOWN)) {
    p->pos.y = MoveWithinGameY(p->pos.y + speed);
  }

  //Met à jour l'animation du joueur
  DrawTextureRec(p->sprite.spritesheet, p->sprite.frameRec, p->location, WHITE);
  UpdateAnimation(&p->sprite);

  //Met à jour le compteur d'invinsibilité
  if (p->invisFrames > 0)
    p->invisFrames--;
}




// int damagePlayer(Player *p, int damage){
// //inflige des dégâts au joueur et le rend invinsible. By-pass l'invinsibilité
// //renvoie 0 si le joueur est tué
//   p->hp -= damage;
//   if (p->hp <= 0)
//       return 0;
//   else{
//       p->invisFrames = INVINSIBILITY_DURATION; 
//       return 1;
//   }
// }


int playerIsAlive(Player p){
    return (p.hp>0);
}
