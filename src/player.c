#include "include/raylib.h"
#include "assets.h"
#include "sprite.h"

#define INVINSIBILITY_DURATION 10

typedef struct {
  Vector2 location; //Corner Up-Left for drawing
  float speed; 
  int hp;
  Sprite sprite;
  int invinsibility; //nombre de frames d'invinsibilité avant que le joueur ne puisse prendre des dégâts

} Player;

int movePlayer(Player *player, Vector2 movement){
//bouge le joueur d'un vecteur2 
  (player->location).x += movement.x;
  (player->location).y += movement.y;
    //il doit bien avoir une fonction pour additionner des vecteurs plus facilement mais bon trkl
}

void initPlayer(Player *p, Vector2 location, float speed, int hp, Sprite sprite){
  p->location = location;
  p->speed = speed;
  p->hp = hp;
  p->sprite = sprite;
  p->invisibility = 0;
}


int damagePlayer(Player *p, int damage){
//inflige des dégâts au joueur et le rend invinsible. By-pass l'invinsibilité
//renvoie 0 si le joueur est tué
  p->hp -= damage;
  if (p->hp <= 0)
      return 0;
  else{
      p->invisibility = INVINSIBILITY_DURATION; 
      return 1;
  }
}


int playerIsAlive(Player p){
    return (p.hp>0);
}
