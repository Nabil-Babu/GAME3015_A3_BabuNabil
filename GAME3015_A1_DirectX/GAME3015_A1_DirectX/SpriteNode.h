#pragma once
#include "Entity.hpp"

class SpriteNode :
    public Entity
{
public:
	SpriteNode(State* state);
	RenderItem* mSpriteNodeRitem;

	void SetMatGeoDrawName(std::string Mat, std::string Geo, std::string DrawName);

private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();

	std::string mMat;
	std::string mGeo;
	std::string mDrawName;
};
