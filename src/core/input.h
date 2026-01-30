#pragma once

#include <raylib.h>

/* Macros */
// NOTE: Pas très joli d'avoir ce genre de truc ici...
#define IS_PRESSED(key) isPressed(ctx.input.key)
#define IS_RELEASED(key) isReleased(ctx.input.key)
#define IS_DOWN(key) isDown(ctx.input.key)

// Configuration des keybinds, modifiable dans les settings
typedef struct InputConfig {
  // NOTE: gardez les memes noms de key pour config et system !
  KeyboardKey up, left, right, down;
  KeyboardKey shoot;
  KeyboardKey bomb;
  KeyboardKey focus;
  KeyboardKey skip;
} InputConfig;

// Etat d'une touche/action (pour remplacer IsKeyDown(...))
typedef struct KeyState {
  int isPressed;
  int isDown;
  int isReleased;
} KeyState;

// Permet de savoir a tout instant chaque etat des touches interessantes
typedef struct InputSystem {
  // NOTE: gardez les memes noms de key pour config et system !
  InputConfig keybinds;

  KeyState up, left, right, down;
  KeyState shoot;
  KeyState bomb;
  KeyState focus;
  KeyState skip;
} InputSystem;

/* Fonctions */
extern void input_initialize(InputSystem * input);
extern void input_update(InputSystem * input);

extern int isPressed(KeyState key);
extern int isDown(KeyState key);
extern int isReleased(KeyState key);

extern void input_change_keybind(KeyboardKey * key, KeyboardKey new_key);
