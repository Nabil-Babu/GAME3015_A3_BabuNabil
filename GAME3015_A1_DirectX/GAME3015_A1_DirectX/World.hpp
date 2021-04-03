#pragma once
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "SpriteNode.h"
#include "CommandQueue.hpp"
#include "Command.hpp"


class World
{
public:
	explicit							World(State* state);
	void								update(const GameTimer& gt);
	void								draw();
	//void								loadTextures();
	void								buildScene();

	CommandQueue&						getCommandQueue();

private:
	CommandQueue						mCommandQueue;

	void								adaptPlayerPosition();
	void								adaptPlayerVelocity();


private:
	enum class Layer
	{
		Background,
		Air
	};


private:
	State* mState;

	SceneNode* mSceneGraph;
	std::array<SceneNode*, 2>	mSceneLayers;

	XMFLOAT4							mWorldBounds;
	XMFLOAT2		    				mSpawnPosition;
	float								mScrollSpeed;
	Aircraft* mPlayerAircraft;
	SpriteNode* mBackground;
	Aircraft* mEnemy;
};
