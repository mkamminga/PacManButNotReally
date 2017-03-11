#pragma once
#include "GamePlayObject.h"
class PacManObject :
	public GamePlayObject
{
public:
	PacManObject() : GamePlayObject(0, 0, nullptr) {}
	void accept(BaseVisitor* bs) {
		bs->visit(this);
	}

	virtual void update(double deltaTime);
};

