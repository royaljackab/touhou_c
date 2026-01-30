#include "core/input.h"
#include "lib/menu.h"
#include "lib/settings.h"
#include "lib/test_task.h"
#include "lib/title_screen.h"
#include <stddef.h>
#include <stdio.h>

varGlobals globals;

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Night of nights");
  SetTargetFPS(60);

  Load_BulletSprites();
  Load_PlayerSprites();
  Load_Players();
  InitPlayer(REIMU_A);
  AssetsLoad();
  initialize();

  init_menu();
  input_initialize(&globals.inputConfig, &globals.inputState);

  load_settings();

  globals.gameState = TITLE_SCREEN;
  globals.pause = 0;

  void *moonlightState = NULL;

  while (!WindowShouldClose()) {
    switch (globals.gameState) {
    case TITLE_SCREEN:
      menu();
      break;
    case MOONLIGHT:

      if (!globals.pause) {
        UpdateObjects();
        moonlight_task(&moonlightState);
        UpdatePlayer();
        UpdateAnimations();
        UpdateAnimationPlayer();
        UpdateCollisions();
        input_update(&globals.inputConfig, &globals.inputState);
      }

      BeginDrawing();
      ClearBackground(BLACK);
      DrawRectangleLines(PANEL_LEFT, PANEL_UP, PANEL_WIDTH, PANEL_HEIGHT,
                         WHITE);

      DrawObjects();
      DrawPlayer();
      EndDrawing();
      break;
    default:
      break;
    }
    if (globals.gameState != TITLE_SCREEN) {
      pauseGame();
    }
    if (globals.pause) {
      pauseMenu();
    }
  }
  AssetsUnload();
  CloseWindow();
}
