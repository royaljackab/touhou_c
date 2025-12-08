#include "assets.h"
#include "globals.h"

#define LOAD_ENTRY(TYPE, FIELD, COUNTER, LOADFN)                    \
    entry = &assets.FIELD##s[assets.COUNTER++];        \
    strcpy(entry->name, name);                                     \
    entry->FIELD = LOADFN(filename);                               \

void LoadAllAssets() {

    /**
     * Load tous les assets du jeu
     * 
     * Utilisation :
     * - Pour un asset de type ENTRY, faire LOAD_ENTRY("nom", "chemin");
     * - Ensuite, dans sprite.h, ajouter dans l'enum correspondant le NOM du sprite
     * - Dans sprite.c, load le sprite correspondant.
     */
    assets.textureCount = assets.imageCount = assets.fontCount = 0;
    assets.soundCount = assets.musicCount = 0;

    //TEXTURES
    const char *name, *filename;
    #define LOAD_TEXTURE(n, f) name = n; filename = f; LOAD_ENTRY(Texture, texture, textureCount, LoadTexture);
    TextureEntry* entry;
    LOAD_TEXTURE("ball_m_black", "../Assets/Sprites/ball_m_black.png");
    LOAD_TEXTURE("anim_test", "../Assets/Sprites/anim_test.png");
    LOAD_TEXTURE("reimu_still", "../Assets/Sprites/reimu_still.png");
    LOAD_TEXTURE("reimu_left", "../Assets/Sprites/reimu_left.png");
    LOAD_TEXTURE("reimu_right", "../Assets/Sprites/reimu_right.png");
    LOAD_TEXTURE("hitbox", "../Assets/Sprites/hitbox.png");
    LOAD_TEXTURE("reimu_pink_amulet", "../Assets/Sprites/reimu_pink_amulet.png");
    LOAD_TEXTURE("fairy_s_blue_still", "../Assets/Sprites/fairy_s_blue_still.png");
    #undef LOAD_TEXTURE

    //IMAGES
    #define LOAD_IMAGE(n, f) name = n; filename = f; LOAD_ENTRY(Image, image, imageCount, LoadImage);
    
    #undef LOAD_IMAGE

    //FONTS
    #define LOAD_FONT(n, f) name = n; filename = f; LOAD_ENTRY(Font, font, fontCount, LoadFont);
    
    #undef LOAD_FONT

    //SOUNDS
    #define LOAD_SOUND(n, f) name = n; filename = f; LOAD_ENTRY(Sound, sound, soundCount, LoadSound);
    
    #undef LOAD_SOUND

    //MUSIC
    #define LOAD_MUSIC(n, f) name = n; filename = f; LOAD_ENTRY(Music, music, musicCount, LoadMusicStream);
    #undef LOAD_MUSIC
}

//Fonctions d’accès

Texture2D GetTexture(const char *name)
{
    for (int i = 0; i < assets.textureCount; i++)
        if (strcmp(assets.textures[i].name, name) == 0)
            return assets.textures[i].texture;
    return (Texture2D){0};
}

Image GetImage(const char *name)
{
    for (int i = 0; i < assets.imageCount; i++)
        if (strcmp(assets.images[i].name, name) == 0)
            return assets.images[i].image;
    return (Image){0};
}

Font GetFont(const char *name)
{
    for (int i = 0; i < assets.fontCount; i++)
        if (strcmp(assets.fonts[i].name, name) == 0)
            return assets.fonts[i].font;
    return (Font){0};
}

Sound GetSound(const char *name)
{
    for (int i = 0; i < assets.soundCount; i++)
        if (strcmp(assets.sounds[i].name, name) == 0)
            return assets.sounds[i].sound;
    return (Sound){0};
}

Music GetMusic(const char *name)
{
    for (int i = 0; i < assets.musicCount; i++)
        if (strcmp(assets.musics[i].name, name) == 0)
            return assets.musics[i].music;
    return (Music){0};
}

//Libération de la mémoire

void UnloadAllAssets()
{
    for (int i = 0; i < assets.textureCount; i++)
        UnloadTexture(assets.textures[i].texture);

    for (int i = 0; i < assets.imageCount; i++)
        UnloadImage(assets.images[i].image);

    for (int i = 0; i < assets.fontCount; i++)
        UnloadFont(assets.fonts[i].font);

    for (int i = 0; i < assets.soundCount; i++)
        UnloadSound(assets.sounds[i].sound);

    for (int i = 0; i < assets.musicCount; i++)
        UnloadMusicStream(assets.musics[i].music);
}