#pragma once
#include "GamePlayObject.h"
#include "CowWandering.h"

class PillItem;

class CowObject : public GamePlayObject
{
public:
	CowObject(int x, int y, std::shared_ptr<GamePlayObject> target) : GamePlayObject(x, y, target) {}
	virtual void accept(BaseVisitor* base);
	virtual void update();
};

