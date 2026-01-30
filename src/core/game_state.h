#pragma once

#include "input.h"
typedef enum StateID {
  STATE_NONE,
  STATE_MENU,
  STATE_PAUSE,
  STATE_SETTINGS,
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

  InputSystem input;

  int debug;
};

extern void gamestate_process_state_change(GameContext *ctx);
