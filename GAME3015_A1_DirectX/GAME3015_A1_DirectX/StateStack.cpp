#include "StateStack.hpp"
#include <cassert>
#include "Game.hpp"

StateStack::StateStack(State::Context context)
	: mStack()
	, mPendingList()
	, mContext(context)
	, mFactories()
{
}

void StateStack::update(const GameTimer& gt)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(gt))
			break;
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	for (State::StatePtr& state : mStack)
		state->draw();
}

void StateStack::handleEvent(WPARAM btnState)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(btnState))
			break;
	}
}

void StateStack::handleRealtimeInput()
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleRealtimeInput())
			break;
	}
}

void StateStack::pushState(States::ID stateID)
{
	mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
	mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
	mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const
{
	return mStack.empty();
}

XMFLOAT3 StateStack::getCameraPos()
{
	if (mStack.size() != 0)
	{
		return mStack.back()->getCameraPos();
	}
	return XMFLOAT3(0.f,0.f,0.f);
}

XMFLOAT3 StateStack::getTargetPos()
{
	if (mStack.size() != 0)
	{
		return mStack.back()->getTargetPos();
	}
	return XMFLOAT3(0.f, 0.f, 0.f);
}

State* StateStack::getCurrentState()
{
	return mStack.back().get();
}

State::StatePtr StateStack::createState(States::ID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());
	return found->second();
}

void StateStack::applyPendingChanges()
{
	for (PendingChange change : mPendingList)
	{
		switch (change.action)
		{
		case Push:
			mStack.push_back(createState(change.stateID));
			break;
		case Pop:
			mStack.pop_back();
			break;
		case Clear:
			mStack.clear();
			break;
		}
	}

	mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
	: action(action)
	, stateID(stateID)
{
}
