#pragma once

#include "input.h"
#include "button.h"

typedef enum StateID {
  STATE_NONE,

  __BEGIN_MENU__,

  STATE_MENU_TITLE,
  STATE_MENU_SETTINGS,
  STATE_MENU_KEYBINDS,

  __END_MENU__,

  STATE_TEST,
  STATE_EXTRA
} StateID;

typedef struct GameContext GameContext;

typedef struct GameState {
  void (*init)(GameContext *ctx);
  void (*update)(GameContext *ctx);
  void (*draw)(GameContext *ctx);
  void (*cleanup)(GameContext *ctx);
} GameState;

struct GameContext {
  StateID currentStateID;
  StateID nextStateID;
  GameState *currentState;

  InputState input;

  ButtonSystem button;

  int debug;
  int pause;
};

void gamestate_process_state_change             (GameContext *ctx);
void pauseListener                              (GameContext *ctx);
void pauseMenu                                  ();
GameState *get_state_pointer                    (StateID state);

extern GameState state_menu_title;
extern GameState state_menu_keybinds;
extern GameState state_test;
