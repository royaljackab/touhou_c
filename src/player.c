#include "player.h"

float angleHitbox=0;
int hitboxAlpha=0;
int shootTimer=0;

#define hitboxColor(alpha) (Color){255,255,255,alpha}

void PlayerInit(Player *p, Vector2 pos, float speed, float focusSpeed, int hp, Sprite sprite){
  /**
   * Initialisation d'un joueur
   */
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
  /**
   * Met à jour la position du joueur en fonction de sa position centrale
   */

  float speed;

  //Si en focus ou pas
  if(IsKeyDown(KEY_LEFT_SHIFT)) {
    speed = p->focusSpeed;
  } else {
    speed = p->speed;
  }

  //Bouge le joueur
  Vector2 movement = {0,0};

  if(IsKeyDown(KEY_RIGHT)) {
    movement.x++;
  }
  if(IsKeyDown(KEY_LEFT)) {
    movement.x--;
  }
  if(IsKeyDown(KEY_UP)) {
    movement.y--;
  }
  if(IsKeyDown(KEY_DOWN)) {
    movement.y++;
  }
  p->pos = Vector2Add(p->pos, Vector2Scale(Vector2Normalize(movement), speed));
  MoveWithinGameVec(p->pos);

  p->location = (Vector2){p->pos.x - p->sprite.collisionOffset.x, p->pos.y - p->sprite.collisionOffset.y};


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

  showHitbox(p);

  shootTimer++;
  if(IsKeyDown(KEY_Z) && shootTimer % 3 == 0) {
    shootTimer = 0;

    int data[MAX_DATA] = {0};
    SpawnBullet((Vector2){p->pos.x + 8, p->pos.y - 40}, (Vector2){0,-1}, 30, Pattern_Straight, data, REIMU_PINK_AMULET, 0, 1);
    SpawnBullet((Vector2){p->pos.x - 8, p->pos.y - 40}, (Vector2){0,-1}, 30, Pattern_Straight, data, REIMU_PINK_AMULET, 0, 1);
  }

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

void showHitbox(Player* p) {

  /**
   * Affiche l'hitbox du joueur, appelée lorsque mode focus activé (shift)
   * L'hitbox tourne sur elle-même, avec un effet fade-in/fade-out
   */

  if(IsKeyPressed(KEY_LEFT_SHIFT)) {
    //fade in
    hitboxAlpha=0;
  }
  if(IsKeyDown(KEY_LEFT_SHIFT)) {
    //Affichage de la hitbox
    angleHitbox += 3;
    hitboxAlpha = Clamp(hitboxAlpha + 30, 0, 255);

    Rectangle recDest = {p->pos.x, p->pos.y, bulletSprites[HITBOX].frameRec.width, bulletSprites[HITBOX].frameRec.height};
    DrawTexturePro(bulletSprites[HITBOX].spritesheet, bulletSprites[HITBOX].frameRec, recDest, (Vector2){32,32}, angleHitbox, hitboxColor(hitboxAlpha));
  }
  //fade out
  if(IsKeyUp(KEY_LEFT_SHIFT) && hitboxAlpha > 0) {
    angleHitbox += 3;
    hitboxAlpha = Clamp(hitboxAlpha - 30,0,255);

    Rectangle recDest = {p->pos.x, p->pos.y, bulletSprites[HITBOX].frameRec.width, bulletSprites[HITBOX].frameRec.height};
    DrawTexturePro(bulletSprites[HITBOX].spritesheet, bulletSprites[HITBOX].frameRec, recDest, (Vector2){32,32}, angleHitbox, hitboxColor(hitboxAlpha));
  }
}