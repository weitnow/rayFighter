#include "SoundManager.h"


SoundManager::SoundManager() : currentBackgroundMusic(nullptr)
{
    // Initialize SoundManager
    InitAudioDevice(); // Initialize audio device

    // Set the path to the music and sound effects
    _setPahToMusic("Assets/Music/");
    _setPathToSoundEffects("Assets/Soundeffects/");

    // Load sound effects (only the ones that are used everywhere in the game, because the rest is loaded in the game-states for the specific states and characters)
    loadSoundEffects("mk2/punchSound.mp3", 1.5f);
    loadSoundEffects("attack.wav", 1.0f);
    loadSoundEffects("ko.mp3");
    loadSoundEffects("bloodSplatter.mp3");
    loadSoundEffects("scream.wav");
    loadSoundEffects("laugh.mp3");
    loadSoundEffects("hitSound.wav", 1.5f);
}


SoundManager::~SoundManager()
{
    // Unload Music
    unloadAllMusic();

    // Unload Sound Effects
    unloadAllSoundEffects();

    // Close audio device
    CloseAudioDevice();
}

void SoundManager::_setPahToMusic(const std::string& path)
{
    musicPath = path;
}

void SoundManager::_setPathToSoundEffects(const std::string& path)
{
    soundEffectsPath = path;
}

void SoundManager::updateBackgroundMusic()
{
    // Check if there is currently playing music
    if (currentBackgroundMusic)
    {
        UpdateMusicStream(*currentBackgroundMusic);
    }
}

void SoundManager::loadMusic(const std::string& filename, const float volume)
{
    // check if music is already in the dictionary
    if (backgroundMusicDict.find(filename) != backgroundMusicDict.end())
    {
        std::cerr << "Music: " << filename << " is already loaded!" << std::endl;
        return;
    }

    // check if musicpath is set
    if (musicPath.empty())
    {
        std::cerr << "Music path is not set!" << std::endl;
        return;
    }

    // Load the music from the specified path
    Music music = LoadMusicStream((musicPath + filename).c_str());

    // set Volume
    SetMusicVolume(music, volume);

    // check if music was loaded
    if (music.stream.buffer == nullptr)
    {
        std::cerr << "Failed to load music: " << filename << std::endl;
        return;
    }

    // add it to the dictionary
    backgroundMusicDict[filename] = music;
}

void SoundManager::unloadMusic(const std::string& filename)
{
    // check if music is already loaded
    if (backgroundMusicDict.find(filename) == backgroundMusicDict.end())
    {
        std::cerr << "Music: " << filename << " is not loaded!" << std::endl;
        return;
    }

    // check if music is currently playing
    if (currentBackgroundMusic == &backgroundMusicDict[filename])
    {
        stopBackgroundMusic();
    }

    // Unload the music from the dictionary
    UnloadMusicStream(backgroundMusicDict[filename]);
    backgroundMusicDict.erase(filename);
}

void SoundManager::unloadAllMusic()
{
    // loop through the dictionary and unload all music
    for (auto& music : backgroundMusicDict)
    {
        UnloadMusicStream(music.second);
    }
}

void SoundManager::playBackgroundMusic(const std::string& filename)
{
    // check if music is already loaded
    if (backgroundMusicDict.find(filename) == backgroundMusicDict.end())
    {
        std::cerr << "Music: " << filename << " is not loaded!" << std::endl;
        return;
    }

    // Stop any currently playing music before starting new music
    if (currentBackgroundMusic)
    {
        stopBackgroundMusic();
    }

    // Set the current music to the one being played
    currentBackgroundMusic = &backgroundMusicDict[filename]; // Store the currently playing music
    PlayMusicStream(*currentBackgroundMusic);
}


void SoundManager::stopBackgroundMusic()
{
    if (currentBackgroundMusic)
    {
        StopMusicStream(*currentBackgroundMusic);
        currentBackgroundMusic = nullptr; // Reset the current music pointer
    }
}

void SoundManager::loadSoundEffects(const std::string& filename, const float volume)
{
    // check if sound effect is already in the dictionary
    if (soundEffectsDict.find(filename) != soundEffectsDict.end())
    {
        std::cerr << "Sound effect: " << filename << " is already loaded!" << std::endl;
        return;
    }

    // check if soundeffectpath is set
    if (soundEffectsPath.empty())
    {
        std::cerr << "Sound effect path is not set!" << std::endl;
        return;
    }

    // Load the sound effect from the specified path
    Sound sound = LoadSound((soundEffectsPath + filename).c_str());

    // set Volume
    SetSoundVolume(sound, volume);

    // check if sound effect was loaded
    if (sound.stream.buffer == nullptr)
    {
        std::cerr << "Failed to load sound effect: " << filename << std::endl;
        return;
    }

    // add it to the dictionary
    soundEffectsDict[filename] = sound;
}

void SoundManager::unloadSoundEffects(const std::string& filename)
{
    // check if sound effect is already loaded
    if (soundEffectsDict.find(filename) == soundEffectsDict.end())
    {
        std::cerr << "Sound effect: " << filename << " is not loaded!" << std::endl;
        return;
    }

    // Unload the sound effect from the dictionary
    UnloadSound(soundEffectsDict[filename]);
    soundEffectsDict.erase(filename);
}

void SoundManager::unloadAllSoundEffects()
{
    // loop through the dictionary and unload all sound effects
    for (auto& sound : soundEffectsDict)
    {
        UnloadSound(sound.second);
    }
}

void SoundManager::playSound(const std::string& filename)
{
    // check if sound effect is already loaded
    if (soundEffectsDict.find(filename) == soundEffectsDict.end())
    {
        std::cerr << "Sound effect: " << filename << " is not loaded!" << std::endl;
        return;
    }

    PlaySound(soundEffectsDict[filename]); // Play the sound effect
}
