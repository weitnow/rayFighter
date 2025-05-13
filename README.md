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
getFrameTag("gbFighter-Punch").frameNumberDuration[43] = 100; // first frame of punch-animation
getFrameTag("gbFighter-Punch").frameNumberDuration[42] = 100; // second frame of punch-animation

here you can also do stuff like this:
getFrameTag("gbFighter-Punch").frameOffsetX = 6; // set the spriteOffsetX for the punch animation
getFrameTag("gbFighter-Death").loop = false; // set loop to false for the death animation

### Frame-Duration (only for a specific Fighter)
In the Fighter::init() you can do stuff like:
getAnimFile()->getFrameTag("gbFighter-Punch").frameNumberDuration[42] =
        100; // set the duration of the frame in milliseconds
getAnimFile()->getFrameTag("gbFighter-Punch").frameNumberDuration[43] =
        100; // set the duration of the frame in milliseconds

### Hitbox/Hurtboxes
BaseGameObjects do have a unorderedMap called CollisionMap which holds collisionBoxes per Frame
like this: collisionBoxesPerFrame["gbFighter-Idle"][0] = List<CollisionBox2D>
Every Gameobject has the following CollisionMaps:
CollisionMap hitBoxesPerFrame;
CollisionMap hurtBoxesPerFrame;
CollisionMap pushBoxesPerFrame;
CollisionMap throwBoxesPerFrame;

Every Gameobj has this methodes to get a list of Collisionboxes. The Methodes takes into consideration
the current Frame the GameObject is in:

List<CollisionBox2D> getPushBoxes();
List<CollisionBox2D> getHitBoxes();
List<CollisionBox2D> getHurtBoxes();
List<CollisionBox2D> getThrowBoxes();

The Collisionboxes has to be added in the init-method of the gameobject like this:

 // [0, 1, 2...] = frameNumber, -1 = valid for all frames of gbFigher (ex. gbFighter-*), -2 = valid for all frames of gbFighter-Action (ex. gbFighter-Idle)
addCollisionBoxForFrame("gbFighter-Idle", -1, CollisionBoxType::PUSHBOX, true, 10, 0, 10, 30);
addCollisionBoxForFrame("gbFighter-Punch", 1, CollisionBoxType::HITBOX, true, 31, 10, 5, 5);
addCollisionBoxForFrame("gbFighter-Idle", -1, CollisionBoxType::HURTBOX, HurtboxType::HEAD, true, 10, 3, 12, 10);

### Statemachine
Every Character is inheriting from BaseCharacter which inherits from BaseGameObject.
Every BaseCharacter has its own States which will be managed by its own Statemachine. You set the needed States in the init-methode of the Character like this:

Dictionary<std::string, std::shared_ptr<State>> customStateMap = 
{{"Idle", std::make_shared<IdleState>()},
{"Walk", std::make_shared<WalkState>()},
{"Jump", std::make_shared<JumpState>()},
{"JumpPunch", std::make_shared<JumpPunchState>()},
{"Duck", std::make_shared<DuckState>()},
{"DuckPunch", std::make_shared<DuckPunchState>()},
{"DuckKick", std::make_shared<DuckKickState>()},
{"DuckBlock", std::make_shared<DuckBlockState>()},
{"Punch", std::make_shared<PunchState>()},
{"Kick", std::make_shared<KickState>()},
{"Block", std::make_shared<BlockState>()},
{"Hit", std::make_shared<HitState>()},
{"Hurt", std::make_shared<HurtState>()},
{"Death", std::make_shared<DeathState>()}};

And then init the StateMachine like this:
getStatemachine().init(customStateMap);

All States inherit from State, which has:
#### Membervariables
- owner          (BaseCharacter*)
- opponent       (BaseCharacter*)
- statemachine   (Statemachine*)
- gameState      (GameState*)
#### Methodes
- checkForHit()
- hasAnimationFinished

### Input
A Instance of InputHandler is created in the Game-Class and called in its update method. The variable inputHandler which holds the instance is valid through all the GameStates. The InputHandler class has has to membervariables, player1Controller and player2Controller, which holds this bools:
- moveLeft
- moveRight
- jump
- duck
- punch
- kick
- block
#### specialmoves
- fireball
- spear
- isLeft 
#### general input
- key_esc
- key_enter
- key_q

## Updatesystem
### Main
main.cpp creates a game-instance which has:
game->update()
game->render()

### Game
game holds a gamestate and does:
void Game::Update()
update inpudHandler
update soundManager
update screen2DManager
update currentGameState

void Game::Render()
render currentGameState

### GameState
if currentGameState holds a instance of gamestate.cpp it does:
void GameState::Update(deltaTime)
_updateIsLeftPlayer1and2()
_updateAllGameObjects(dt)
_updateAllBaseCharacters(dt)
player1->update(dt)
player2->update(dt)
_checkPushCollsionBetweenPlayers()
_updateMIddlePointBetweenPlayers()
_updateCamera()
_keepPlayerOnstage();
_levelAnimFile->update(dt)
gui->update(dt)

### Player
the update-method of players (basecharacter.cpp) does:
_updateCollsionBoxes(dt)
update position
_reducePushVector(dt)
apply gravity
statemachine->update(dt)
_updateCharacterController
update animfilePtr

### Statemachine
Statemachine holds a State-Instance as Membervariable and does:
currentState->Update(dt)

### State



## Todos
Implement fireball as specialmove and see how well it works with the current hitbox and statemachine system
