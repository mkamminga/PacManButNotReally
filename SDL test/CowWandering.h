#pragma once
#include "BaseState.h"
#include "GraphNode.h"

class CowWandering : public BaseState
{
private:
	std::shared_ptr<GraphNode> lastVisited[2];
public:
	CowWandering(std::shared_ptr<GamePlayObject> object) : BaseState(object) {}
	virtual void update();
	virtual void check();
};

