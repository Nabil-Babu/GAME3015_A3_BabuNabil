#include "OptionState.h"
#include "SpriteNode.h"
#include "Game.hpp"

OptionState::OptionState(StateStack* stack, Context* context) : State(stack, context)
{
    mAllRitems.clear();
    mContext->game->ResetFrameResources();
    //mContext->game->BuildMaterials();

    std::unique_ptr<SpriteNode> backgroundSprite = std::make_unique<SpriteNode>(this);
    backgroundSprite->SetMatGeoDrawName("StarWars_Option", "boxGeo", "box");
    backgroundSprite->setScale(11.5, 1.0, 10.0);
    backgroundSprite->setPosition(0, 0, 0);
    mSceneGraph->attachChild(std::move(backgroundSprite));

    mSceneGraph->build();
    mContext->game->BuildFrameResources(mAllRitems.size());

}

OptionState::~OptionState()
{
}

void OptionState::draw()
{
    mSceneGraph->draw();
}

bool OptionState::update(const GameTimer& gt)
{
    mSceneGraph->update(gt);

    return true;
}

bool OptionState::handleEvent(WPARAM btnState)
{
    // 1 - Arrow Keys


    // 2 - WASD


    // B - Back


    return true;
}

bool OptionState::handleRealtimeInput()
{
    return true;
}
