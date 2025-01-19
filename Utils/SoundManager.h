#ifndef GBFIGHTER_SOUNDMANAGER_H
#define GBFIGHTER_SOUNDMANAGER_H

#include "Core.h"
#include "raylib.h"
#include <string>

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

    // needs to be called in the main loop
    void updateBackgroundMusic();

    // <-- Background Music -->
    // Loading and unloading music and setting volume
    void loadMusic(const std::string& filename, const float volume = 1.f);
    void unloadMusic(const std::string& filename);
    void unloadAllMusic();
    // Playing and stopping music
    void playBackgroundMusic(const std::string& filename);
    void stopBackgroundMusic();

    // <-- Sound Effects -->
    // Loading and unloading sound effects
    void loadSoundEffects(const std::string& filename, const float volume = 1.f);
    void unloadSoundEffects(const std::string& filename);
    void unloadAllSoundEffects();
    // Playing sound effects
    void playSound(const std::string& filename);


private:
    SoundManager(); // Private constructor to prevent direct instantiation

    // needs to be called once before using the SoundManager
    void _setPahToMusic(const std::string& path);
    void _setPathToSoundEffects(const std::string& path);

    // Prevent copying
    SoundManager(const SoundManager&) = delete;            // Delete copy constructor
    SoundManager& operator=(const SoundManager&) = delete; // Delete copy assignment operator

    // Store the currently playing background music
    Music* currentBackgroundMusic; // Pointer to the currently playing music
    Dictionary<std::string, Music> backgroundMusicDict;

    // Store sound effects
    Dictionary<std::string, Sound> soundEffectsDict;


    std::string musicPath;
    std::string soundEffectsPath;
};

#endif //GBFIGHTER_SOUNDMANAGER_H
