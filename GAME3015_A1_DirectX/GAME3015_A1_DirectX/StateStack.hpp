#pragma once

#include "State.hpp"
#include "StateIdentifiers.hpp"

#include <vector>
#include <utility>
#include <functional>
#include <map>

class StateStack
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};
public:
	explicit StateStack(State::Context context);
	
	template <typename T>
	void registerState(States::ID stateID);

	void update(const GameTimer& gt);
	void draw();
	void handleEvent(WPARAM btnState);
	void handleRealtimeInput();

	void pushState(States::ID stateID);
	void popState();
	void clearStates();

	bool isEmpty() const;

	XMFLOAT3 getCameraPos();
	XMFLOAT3 getTargetPos();
	State* getCurrentState();
private:
	State::StatePtr createState(States::ID stateID);
	void applyPendingChanges();

private:
	struct PendingChange
	{
		explicit			PendingChange(Action action, States::ID stateID = States::None);

		Action				action;
		States::ID			stateID;
	};

private:
	std::vector<State::StatePtr>	mStack;
	std::vector<PendingChange>	mPendingList;

	State::Context	mContext;
	std::map<States::ID, std::function<State::StatePtr()>> mFactories;
};


template <typename T>
void StateStack::registerState(States::ID stateID)
{
	mFactories[stateID] = [this]()
	{
		return State::StatePtr(new T(this, &mContext));
	};
}

