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

  //change les animations du joueur en fonction de sa direction
  if(IsKeyPressed(KEY_RIGHT)){  //droite
    p->sprite = bulletSprites[REIMU_RIGHT];
  }
  else if(IsKeyPressed(KEY_LEFT)){ //gauche
    p->sprite = bulletSprites[REIMU_LEFT];
  }
  if( (IsKeyReleased(KEY_RIGHT) && IsKeyUp(KEY_LEFT)) || (IsKeyReleased(KEY_LEFT) && IsKeyUp(KEY_RIGHT)) 
  || (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT))){   //immobile
    p->sprite = bulletSprites[REIMU_STILL];
  }

  //Met à jour l'animation du joueur
  DrawTextureRec(p->sprite.spritesheet, p->sprite.frameRec, p->location, WHITE);
  UpdateAnimation(&p->sprite);

  //Met à jour le compteur d'invinsibilité
  if (p->invisFrames > 0)
    p->invisFrames--;


  //verifie les colisions et applique les dégâts
  int damage = playerIsColliding(p);
  damagePlayer(p, damage);
  char strHP[15];
  
  sprintf(strHP, "HP : %d", p->hp);
  DrawText(strHP, 20 , 100, 20, GREEN);
}


int playerIsColliding(Player *player ){
//renvoie les degats pris par la 1ere bullet qui touche le joueur sur ce tick

  if(player->invisFrames==0){
    for (int i = 0; i < nbBullets; i++) {
      int collision = CheckCollisionCircles(player->location , player->sprite.collisionRadius, bullets[i].location, bullets[i].sprite.collisionRadius);
      if (collision){
        DrawText("AIE AIE TOUCHÉ", 20 , 70, 20, RED);
        return bullets[i].bDamage;
      }
    }
  }
  return 0;
  
}

 int damagePlayer(Player *p, int damage){
 //inflige des dégâts au joueur et le rend invinsible. By-pass l'invinsibilité
 //renvoie 0 si le joueur est tué
 if (damage!=0){
    p->hp -= damage;
    if (p->hp <= 0)
      return 0;
    else{
        p->invisFrames = INVINSIBILITY_DURATION; 
        return 1;
    }
 }
 return 1;
 }


int playerIsAlive(Player p){
    return (p.hp>0);
}
