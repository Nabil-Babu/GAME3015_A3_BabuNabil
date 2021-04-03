#pragma once
#include "State.hpp"
class TitleState :
    public State
{
public:
    TitleState(StateStack* stack, Context* context);
    virtual ~TitleState();
    virtual void draw()override;
    virtual bool update(const GameTimer& gt)override;
    virtual bool handleEvent(WPARAM btnState)override;
    virtual bool handleRealtimeInput()override;

};

