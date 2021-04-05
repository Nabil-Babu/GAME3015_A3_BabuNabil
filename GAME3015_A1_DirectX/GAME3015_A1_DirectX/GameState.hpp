#pragma once

#include "State.hpp"
#include "World.hpp"
#include "Player.hpp"

class GameState :
    public State
{
public:
    GameState(StateStack* stack, Context* context);
    virtual ~GameState();
    virtual void draw()override;
    virtual bool update(const GameTimer& gt)override;
    virtual bool handleEvent(WPARAM btnState)override;
    virtual bool handleRealtimeInput()override;

    void ProcessInput();
private:
    World mWorld;
};

