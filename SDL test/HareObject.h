#pragma once
#include "GamePlayObject.h"
class HareObject :
	public GamePlayObject
{
public:
	HareObject(int x, int y,  std::shared_ptr<GamePlayObject> target) : GamePlayObject(x, y, target) {}
	virtual void accept(BaseVisitor* base);
	virtual void update();
};

