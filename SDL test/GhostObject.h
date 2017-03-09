#pragma once
#include "GamePlayObject.h"
class GhostObject :
	public GamePlayObject
{
public:
	GhostObject() : GamePlayObject(0, 0) {}
	void accept(BaseVisitor* bs ) {
		bs->visit(this);
	}

	virtual void update(double deltaTime);
};

