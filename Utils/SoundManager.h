#ifndef GBFIGHTER_SOUNDMANAGER_H
#define GBFIGHTER_SOUNDMANAGER_H

#include "Core.h"
#include "raylib.h"

class SoundManager
{
public:
    // Method to access the single instance of the class
    static SoundManager& getInstance()
    {
        static SoundManager instance;
        return instance;
    }
    ~SoundManager();

    void updateBackgroundMusic();

    void playBackgroundMusic(Music& backgroundMusic);
    void playRandomBackgroundMusic();
    void playSound(Sound& sound);
    void stopBackgroundMusic();
    void stopSound(Sound& sound);


    // Background Music Objects
    Music bison_music;
    Music countryyard_music;
    Music feilong_music;
    Music guile_music;
    Music ken_music;
    Music killerinstinct_music;
    Music ryu_music;
    Music sagat_music;
    Music zangief_music;

    // Sound Effects Objects
    Sound hitSound;
    Sound punchSound;
    Sound ko;
    Sound bloodSplatter;

private:
    SoundManager(); // Private constructor to prevent direct instantiation

    // Store the currently playing background music
    Music* currentBackgroundMusic;    // Pointer to the currently playing music
    List<Music*> backgroundMusicList; // List of all background music

    // Prevent copying
    SoundManager(const SoundManager&) = delete;            // Delete copy constructor
    SoundManager& operator=(const SoundManager&) = delete; // Delete copy assignment operator
};

#endif //GBFIGHTER_SOUNDMANAGER_H
