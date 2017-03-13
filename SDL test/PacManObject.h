#pragma once
#include "GamePlayObject.h"
class PacManObject :
	public GamePlayObject
{
public:
	PacManObject(int speed) : GamePlayObject(0, 0, nullptr, speed, 0, 0) {}
	void accept(BaseVisitor* bs) {
		bs->visit(this);
	}

	virtual void update(double deltaTime);
};

