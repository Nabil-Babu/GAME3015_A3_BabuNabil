#include "PauseState.h"
#include "SpriteNode.h"
#include "Game.hpp"

PauseState::PauseState(StateStack* stack, Context* context) : State(stack, context)
{
    mAllRitems.clear();
    mContext->game->ResetFrameResources();
    //mContext->game->BuildMaterials();

    std::unique_ptr<SpriteNode> backgroundSprite = std::make_unique<SpriteNode>(this);
    backgroundSprite->SetMatGeoDrawName("StarWars_Pause", "boxGeo", "box");
    backgroundSprite->setScale(11.5, 1.0, 10.0);
    backgroundSprite->setPosition(0, 0, 0);
    mSceneGraph->attachChild(std::move(backgroundSprite));

    mSceneGraph->build();
    mContext->game->BuildFrameResources(mAllRitems.size());
}

PauseState::~PauseState()
{
}

void PauseState::draw()
{
    mSceneGraph->draw();
}

bool PauseState::update(const GameTimer& gt)
{
    mSceneGraph->update(gt);

    return true;
}

bool PauseState::handleEvent(WPARAM btnState)
{
    // P - Resume


    // Q - Quit to Menu


    return true;
}

bool PauseState::handleRealtimeInput()
{
    return true;
}
