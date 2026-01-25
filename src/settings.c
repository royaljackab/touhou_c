#include "globals.h"
#include <stdio.h>
#include <string.h>

// KEY_RIGHT           = 262,      // Key: Cursor right
// KEY_LEFT            = 263,      // Key: Cursor left
// KEY_DOWN            = 264,      // Key: Cursor down
// KEY_UP              = 265,      // Key: Cursor up

void init_settings(){
    //créé le fichier settings.txt si il n'existe pas.
}

void load_settings(){
    char optionName[30];
    int optionValue;
    FILE * f = fopen("../settings.txt","r");

    if(!f){
        init_settings();
        return;
    }
    printf("options chargées avec succès\n");
    while(fscanf(f," %29[^=]=%d",optionName,&optionValue) != EOF){
        //------ keybinds ------
        if(strcmp(optionName,"keybind_move_left") == 0){
            printf("left set to %d\n",optionValue);
            globals.keybind_move_left = optionValue;
        }
        else if(strcmp(optionName,"keybind_move_right") == 0){
            printf("right set to %d\n",optionValue);
            globals.keybind_move_right = optionValue;
        }
        else if(strcmp(optionName,"keybind_move_down") == 0){
            printf("down set to %d\n",optionValue);
            globals.keybind_move_down = optionValue;
        }
        else if(strcmp(optionName,"keybind_move_up") == 0){
            printf("up set to %d\n",optionValue);
            globals.keybind_move_up = optionValue;
        }
        else if(strcmp(optionName,"keybind_shoot") == 0){
            printf("shoot set to %d\n",optionValue);
            globals.keybind_shoot = optionValue;
        }
        else if(strcmp(optionName,"keybind_pause") == 0){
            printf("pause set to %d\n",optionValue);
            globals.keybind_pause = optionValue;
        }
        else if(strcmp(optionName,"keybind_focus_mode") == 0){
            printf("focus mode set to %d\n",optionValue);
            globals.keybind_focus_mode = optionValue;
        }
        else if(strcmp(optionName,"keybind_validate") == 0){
            printf("validate set to %d\n",optionValue);
            globals.keybind_validate = optionValue;
        }
    }
    fclose(f);
}
