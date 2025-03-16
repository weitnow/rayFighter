# rayFighter

SF2 / MK2 like game with gameboy-graphics written in c++ with raylib



## Preview
[preview on youtube](https://www.youtube.com/watch?v=svkh_CahTW8)
![](https://github.com/weitnow/rayFighter/blob/master/preview.png)


## Development-Notes

### Frame-Duration (global)
They are specified in the json-file generated from aseprite. The json-file has frameTags
for example gbFighter-Idle (frame 0 to 2). Each Frame (0, 1, 2) has a duration in ms.
main.cpp creates a game-instance which creates a asepriteManager-Instance, which has
a init-methods which loads the frameTags. The asepriteManager-Instance has a method
which returns a AsepriteAnimationFile, which will get attached to a gameObject (for example
the character of player 1 and 2). The AsepriteAnimationFile->getFrameTag("gbFighter-Idle)
returns the gbFigher-Idle-Frametag which has from (first frame) and to (last frame) and
frameOffsetX and frameOffsetY as well as a frameNumberDuration which is a unordered map
([frameNumber] = duration in ms)

Either you set Frame-Duration in Aseprite an therefore in JSON or you override the value while loading
the jsonfile in void AsepriteManager::init() like this:
    getFrameTag("gbFighter-Punch").frameNumberDuration[43] =
        100; // set the duration of the first frame of the punch animation
    getFrameTag("gbFighter-Punch").frameNumberDuration[42] =
        100; // set the duration of the second frame of the punch animation

here you can also do stuff like this:
getFrameTag("gbFighter-Punch").frameOffsetX = 6; // set the spriteOffsetX for the punch animation
getFrameTag("gbFighter-DuckPunch").frameOffsetX = 6;
getFrameTag("gbFighter-DuckBlock").frameOffsetX = -2;
getFrameTag("gbFighter-Death").loop = false; // set loop to false for the death animation

### Frame-Duration (only for a specific Fighter)
In the Fighter::init() you can do stuff like:
getAnimFile()->getFrameTag("gbFighter-Punch").frameNumberDuration[42] =
        100; // set the duration of the frame in milliseconds
getAnimFile()->getFrameTag("gbFighter-Punch").frameNumberDuration[43] =
        100; // set the duration of the frame in milliseconds
