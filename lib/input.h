#pragma once

#include <raylib.h>
// Configuration des keybinds, modifiable dans les settings
typedef struct InputConfig {
  // NOTE: gardez les memes noms de key pour config et State !
  KeyboardKey up, left, right, down;
  KeyboardKey shoot;
  KeyboardKey bomb;
  KeyboardKey focus;
  KeyboardKey skip;
  KeyboardKey pause;
  KeyboardKey validate;
} InputConfig;

// Etat d'une touche/action (pour remplacer IsKeyDown(...))
typedef struct KeyState {
  int isPressed;
  int isDown;
  int isReleased;
} KeyState;

// Permet de savoir a tout instant chaque etat des touches interessantes
typedef struct InputState {
  // NOTE: gardez les memes noms de key pour config et State !
  InputConfig keybinds;

  KeyState up, left, right, down;
  KeyState shoot;
  KeyState bomb;
  KeyState focus;
  KeyState skip;
  KeyState pause;
  KeyState validate;
} InputState;

/* Fonctions */
extern void input_initialize(InputState * input);
extern void input_update(InputState * input);

extern int isPressed(KeyState key);
extern int isDown(KeyState key);
extern int isReleased(KeyState key);

extern void input_change_keybind(KeyboardKey * key, KeyboardKey new_key);
