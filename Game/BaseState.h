#ifndef BASE_STATE_H
#define BASE_STATE_H


//forward declaration of game
class Game;

class BaseState
{
public:
    BaseState(Game* game) : game(game)
    {
    }
    virtual ~BaseState()
    {
    }
    virtual void Enter();
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Exit() = 0;

protected:
    Game* game;
};


#endif // GB_BASE_STATE_H
