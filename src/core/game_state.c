#include "game_state.h"
#include <stddef.h>

static GameState *get_state_pointer(StateID state) {
  /***
   * @return: pointeur vers l'état désigné par state
   */

  // NOTE: Nouvel état = Nouveau case ici !
  switch (state) {
  case STATE_MENU:
    return &state_menu;
  case STATE_TEST:
    return &state_test;
  default:
    return 0;
  }
}

void gamestate_process_state_change(GameContext *ctx) {
  /***
   * Appelée a chaque frame pour effectuer le changement d'état (s'il a lieu)
   */

  // Pas de changement d'état
  if (ctx->nextStateID == STATE_NONE) {
    return;
  }

  // On nettoie l'état précédent
  if (ctx->currentState != NULL) {
    ctx->currentState->cleanup(ctx);
  }
  // Changer l'ID et pointeur
  ctx->currentStateID = ctx->nextStateID;
  ctx->currentState = get_state_pointer(ctx->currentStateID);

  // Initialiser le nouvel etat
  if (ctx->currentState != NULL) {
    ctx->currentState->init(ctx);
  }

  // Reset trigger
  ctx->nextStateID = STATE_NONE;
}
