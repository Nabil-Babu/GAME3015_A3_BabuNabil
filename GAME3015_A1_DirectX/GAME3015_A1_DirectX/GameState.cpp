#include "GameState.hpp"
#include "Game.hpp"

GameState::GameState(StateStack* stack, Context* context)
	: State(stack, context)
	, mWorld(this)
{
	mAllRitems.clear();
	mContext->game->ResetFrameResources();
	
	mWorld.buildScene();
	
	mContext->game->BuildFrameResources(mAllRitems.size());
}

GameState::~GameState()
{
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(const GameTimer& gt)
{
	ProcessInput();

	mWorld.update(gt);

	return true;
}

bool GameState::handleEvent(WPARAM btnState)
{
	// Nothing for now
	
	return true;
}

bool GameState::handleRealtimeInput()
{
	// Nothing for now
	return true;
}

void GameState::ProcessInput()
{
	CommandQueue& commands = mWorld.getCommandQueue();
	mContext->player->handleEvent(commands);
	mContext->player->handleRealtimeInput(commands);
}
