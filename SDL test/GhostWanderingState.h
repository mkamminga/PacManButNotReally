#pragma once
#include "PacManBaseState.h"
#include "GraphNode.h"
#include "BasicTimer.h"
#include <memory>
#include <iostream>

class GhostWanderingState :
	public PacManBaseState, public BasicTimerRegisterAble, public std::enable_shared_from_this<BasicTimerRegisterAble>
{
private:
	bool registerd = false;
	int wanderingTime = 0;
public:
	GhostWanderingState(std::shared_ptr<GamePlayObject> object, int wanderingTime) : wanderingTime(wanderingTime), PacManBaseState(object) {}
	virtual void check();
	virtual void accept(BaseVisitor* bv, BaseObject* bo);
	virtual void tick();
};

