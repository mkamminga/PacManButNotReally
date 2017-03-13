#pragma once
#include "GamePlayObject.h"
#include "PacManObject.h"

class GhostObject :
	public GamePlayObject
{
private :
	int wanderingTime = 8;
public:
	GhostObject(std::shared_ptr<PacManObject> pacManObject, int speed, int speedmultiplier, int wanderingTime) : GamePlayObject(0, 0, pacManObject, speed, speedmultiplier, wanderingTime) {}

	void accept(BaseVisitor* bs);
	virtual void update(double deltaTime);
};

