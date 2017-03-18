#pragma once
#include "PacManBaseState.h"
#include "GhostBaseState.h"
#include "GraphNode.h"
#include "BasicTimer.h"
#include <memory>
#include <iostream>

class GhostWanderingState :
	public GhostBaseState,  public BasicTimerRegisterAble, public std::enable_shared_from_this<BasicTimerRegisterAble>
{
private:
	bool registerd = false;
	int wanderingTime = 0;
	std::shared_ptr<GraphNode> lastVisited[2];
public:
	GhostWanderingState(std::shared_ptr<GamePlayObject> object, std::shared_ptr<GhostManager> ghostManager) : GhostBaseState(object, ghostManager) 
	{
		this->wanderingTime = object->getWanderingTime();
	}
	virtual void check();
	virtual void update(double deltaTime);
	virtual void accept(BaseVisitor* bv, BaseObject* bo);
	virtual void tick();
};