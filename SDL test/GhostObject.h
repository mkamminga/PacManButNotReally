#pragma once
#include "GamePlayObject.h"
#include "GhostBaseState.h"

class GhostObject :
	public GamePlayObject
{
protected:
	int wanderingTime = 8;
public:
	GhostObject(std::shared_ptr<GamePlayObject> pacManObject, int speed, int speedmultiplier, int wanderingTime) : GamePlayObject(0, 0, pacManObject, speed, speedmultiplier, wanderingTime) {}
	void accept(BaseVisitor* bs);
	virtual void update(double deltaTime);
};

