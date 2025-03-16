# rayFighter

SF2 / MK2 like game with gameboy-graphics written in c++ with raylib



## Preview
[preview on youtube](https://www.youtube.com/watch?v=svkh_CahTW8)
![](https://github.com/weitnow/rayFighter/blob/master/preview.png)


## Development-Notes

### Frame-Timing
They are specified in the json-file generated from aseprite. The json-file has frameTags
for example gbFighter-Idle (frame 0 to 2). Each Frame (0, 1, 2) has a duration in ms.
main.cpp creates a game-instance which creates a asepriteManager-Instance, which has
a init-methods which loads the frameTags. The asepriteManager-Instance has a method
which returns a AsepriteAnimationFile, which will get attached to a gameObject (for example
the character of player 1 and 2). The AsepriteAnimationFile->getFrameTag("gbFighter-Idle)
returns the gbFigher-Idle-Frametag which has from (first frame) and to (last frame) and
frameOffsetX and frameOffsetY as well as a frameNumberDuration which is a unordered map
([frameNumber] = duration in ms)
