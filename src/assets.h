#ifndef ASSETS_H
#define ASSETS_H

#include "include/raylib.h"

#define MAX_ASSETS 500

typedef struct {
    char name[32];
    Texture2D texture;
} TextureEntry;

typedef struct {
    char name[32];
    Image image;
} ImageEntry;

typedef struct {
    char name[32];
    Font font;
} FontEntry;

typedef struct {
    char name[32];
    Sound sound;
} SoundEntry;

typedef struct {
    char name[32];
    Music music;
} MusicEntry;

typedef struct {
    TextureEntry textures[MAX_ASSETS];
    ImageEntry images[MAX_ASSETS];
    FontEntry fonts[MAX_ASSETS];
    SoundEntry sounds[MAX_ASSETS];
    MusicEntry musics[MAX_ASSETS];

    int textureCount;
    int imageCount;
    int fontCount;
    int soundCount;
    int musicCount;
} Assets;

// Fonctions de gestion
void LoadAllAssets();
void UnloadAllAssets();

// Fonctions d’accès
Texture2D GetTexture(const char *name);
Image GetImage(const char *name);
Font GetFont(const char *name);
Sound GetSound(const char *name);
Music GetMusic(const char *name);

#endif
