#include "State.hpp"
#include "StateStack.hpp"
#include "SceneNode.hpp"
#include "Game.hpp"

State::Context::Context(Game* _game, Player* _player)
	: game(_game), 
	player(_player)
{
}

State::State(StateStack* stack, Context* context)
	: mStack(stack)
	, mContext(context)
	, mCameraPos(0.f, 0.f, 0.f)
	, mSceneGraph(std::make_unique<SceneNode>(this))
{
}

State::~State()
{
}


State::Context* State::getContext() const
{
	return mContext;
}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}


