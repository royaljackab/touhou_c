#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "globals.h"

#define DECLARE_BUTTON_GET_KEY_FUNCTION(TARGET_BIND) \
    void button_getKey_##TARGET_BIND(void) { \
        button_getKey_(#TARGET_BIND, &globals.keybind_##TARGET_BIND); \
    }

void init_menu                  ();
void button_notImplemented      ();
void button_moonlight           ();
void button_getKey_             (const char* target_name, KeyboardKey* key_target);
void button_getKey_move_left    ();
void button_getKey_move_right   ();
void button_getKey_move_up      ();
void button_getKey_move_down    ();
void button_getKey_shoot        ();
void button_getKey_pause        ();
void button_getKey_validate     ();
void button_getKey_focus_mode   ();

#endif