#include "../lib/globals.h"
#include <stdio.h>
#include <string.h>

// KEY_RIGHT           = 262,      // Key: Cursor right
// KEY_LEFT            = 263,      // Key: Cursor left
// KEY_DOWN            = 264,      // Key: Cursor down
// KEY_UP              = 265,      // Key: Cursor up

void init_settings(){
    //créé le fichier settings.txt si il n'existe pas.
    
    //------------ Valeurs par défaut des options ------------
    //------ keybinds ------
    globals.keybind_move_left=KEY_LEFT;
    globals.keybind_move_right=KEY_RIGHT;
    globals.keybind_move_down=KEY_DOWN;
    globals.keybind_move_up=KEY_UP;
    globals.keybind_shoot=KEY_Z;
    globals.keybind_pause=KEY_P;
    globals.keybind_focus_mode=KEY_LEFT_SHIFT;
    globals.keybind_validate=KEY_SPACE;
    
    FILE *new = fopen("../settings.txt", "w");
    if(!new){
        return;
    }
    //------------ Création du fichier ------------
    //------ keybinds ------
    fprintf(new,"keybind_move_left=%d\n",globals.keybind_move_left);
    fprintf(new,"keybind_move_right=%d\n",globals.keybind_move_right);
    fprintf(new,"keybind_move_down=%d\n",globals.keybind_move_down);
    fprintf(new,"keybind_move_up=%d\n",globals.keybind_move_up);
    fprintf(new,"keybind_shoot=%d\n",globals.keybind_shoot);
    fprintf(new,"keybind_pause=%d\n",globals.keybind_pause);
    fprintf(new,"keybind_focus_mode=%d\n",globals.keybind_focus_mode);
    fprintf(new,"keybind_validate=%d\n",globals.keybind_validate);
    fclose(new);
}

void load_settings(){
    char optionName[50];
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

void saveSettings(){
    FILE *new = fopen("../temp.txt", "w");
    char optionName[50];
    FILE *old = fopen("../settings.txt","r");
    int dummy;
    if(!old || !new){
        return;
    }

    while(fscanf(old," %29[^=]=%d",optionName,&dummy) != EOF){
        //------ keybinds ------
        if(strcmp(optionName,"keybind_move_left") == 0){
            fprintf(new,"%s=%d\n",optionName,globals.keybind_move_left);
        }
        else if(strcmp(optionName,"keybind_move_right") == 0){
            fprintf(new,"%s=%d\n",optionName,globals.keybind_move_right);
        }
        else if(strcmp(optionName,"keybind_move_down") == 0){
            fprintf(new,"%s=%d\n",optionName,globals.keybind_move_down);
        }
        else if(strcmp(optionName,"keybind_move_up") == 0){
            fprintf(new,"%s=%d\n",optionName,globals.keybind_move_up);
        }
        else if(strcmp(optionName,"keybind_shoot") == 0){
            fprintf(new,"%s=%d\n",optionName,globals.keybind_shoot);
        }
        else if(strcmp(optionName,"keybind_pause") == 0){
            fprintf(new,"%s=%d\n",optionName,globals.keybind_pause);
        }
        else if(strcmp(optionName,"keybind_focus_mode") == 0){
            fprintf(new,"%s=%d\n",optionName,globals.keybind_focus_mode);
        }
        else if(strcmp(optionName,"keybind_validate") == 0){
            fprintf(new,"%s=%d\n",optionName,globals.keybind_validate);
        }
    }
    fclose(old);
    fclose(new);
    

    remove("../settings.txt");
    rename("../temp.txt", "../settings.txt");
}


