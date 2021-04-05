#pragma once
#include "State.hpp"

class OptionState : public State
{
public:
    OptionState(StateStack* stack, Context* context);
    virtual ~OptionState();
    virtual void draw()override;
    virtual bool update(const GameTimer& gt)override;
    virtual bool handleEvent(WPARAM btnState)override;
    virtual bool handleRealtimeInput()override;
};