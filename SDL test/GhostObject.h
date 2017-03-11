#pragma once
#include "GamePlayObject.h"
#include "PacManObject.h"

class GhostObject :
	public GamePlayObject
{
public:
	GhostObject(std::shared_ptr<PacManObject> pacManObject) : GamePlayObject(0, 0, pacManObject) {}

	void accept(BaseVisitor* bs);
	virtual void update(double deltaTime);
};

