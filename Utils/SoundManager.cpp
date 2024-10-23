#include "SoundManager.h"
#include <cstdlib> // For rand()
#include <ctime>   // For time()

SoundManager::SoundManager() : currentBackgroundMusic(nullptr)
{
    // Initialize SoundManager
    InitAudioDevice(); // Initialize audio device

    // Load background music
    bison_music = LoadMusicStream("Assets/Music/bison_music.mp3");
    countryyard_music = LoadMusicStream("Assets/Music/countryyard_music.mp3");
    feilong_music = LoadMusicStream("Assets/Music/feilong_music.mp3");
    guile_music = LoadMusicStream("Assets/Music/guile_music.mp3");
    ken_music = LoadMusicStream("Assets/Music/ken_music.mp3");
    killerinstinct_music = LoadMusicStream("Assets/Music/killerinstinct_music.mp3");
    ryu_music = LoadMusicStream("Assets/Music/ryu_music.mp3");
    sagat_music = LoadMusicStream("Assets/Music/sagat_music.mp3");
    zangief_music = LoadMusicStream("Assets/Music/zangief_music.mp3");

    // Store all background music in a list
    backgroundMusicList = {&bison_music,
                           &countryyard_music,
                           &feilong_music,
                           &guile_music,
                           &ken_music,
                           &killerinstinct_music,
                           &ryu_music,
                           &sagat_music,
                           &zangief_music};

    // Load sound effects
    hitSound = LoadSound("Assets/Soundeffects/2BH.wav");
    punchSound = LoadSound("Assets/Soundeffects/mk2/mk2-00136.mp3");
    ko = LoadSound("Assets/Soundeffects/ko.mp3");
}


SoundManager::~SoundManager()
{
    // Unload Music
    UnloadMusicStream(feilong_music);
    UnloadMusicStream(bison_music);
    UnloadMusicStream(countryyard_music);
    UnloadMusicStream(guile_music);
    UnloadMusicStream(ken_music);
    UnloadMusicStream(killerinstinct_music);
    UnloadMusicStream(ryu_music);
    UnloadMusicStream(sagat_music);
    UnloadMusicStream(zangief_music);

    // Unload Sound Effects
    UnloadSound(hitSound);
    UnloadSound(punchSound);
    UnloadSound(ko);

    // Close audio device
    CloseAudioDevice();
}

void SoundManager::updateBackgroundMusic()
{
    // Check if there is currently playing music
    if (currentBackgroundMusic)
    {
        UpdateMusicStream(*currentBackgroundMusic);
    }
}

void SoundManager::playBackgroundMusic(Music& backgroundMusic)
{
    // Stop any currently playing music before starting new music
    if (currentBackgroundMusic)
    {
        stopBackgroundMusic();
    }

    // Set the current music to the one being played
    currentBackgroundMusic = &backgroundMusic; // Store the currently playing music
    PlayMusicStream(backgroundMusic);
}

void SoundManager::playRandomBackgroundMusic()
{
    // Select a random index from the musicTracks vector
    int randomIndex = std::rand() % backgroundMusicList.size();

    // Play the selected random music
    playBackgroundMusic(*backgroundMusicList[randomIndex]);
}

void SoundManager::playSound(Sound& sound)
{
    PlaySound(sound); // Play the sound effect
}

void SoundManager::stopBackgroundMusic()
{
    if (currentBackgroundMusic)
    {
        StopMusicStream(*currentBackgroundMusic);
        currentBackgroundMusic = nullptr; // Reset the current music pointer
    }
}

void SoundManager::stopSound(Sound& sound)
{
    StopSound(sound); // Stop the sound effect
}
