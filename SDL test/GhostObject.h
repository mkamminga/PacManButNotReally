#pragma once
#include "GamePlayObject.h"
class GhostObject :
	public GamePlayObject
{
public:
	void accept(BaseVisitor* bs ) {
		bs->visit(this);
	}

	virtual void update();
};
