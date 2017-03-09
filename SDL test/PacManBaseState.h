#pragma once
#include "BaseState.h"
#include "GraphNode.h"

class PacManBaseState :
	public BaseState
{
private:
	std::shared_ptr<GraphNode> lastVisited[2];
	std::shared_ptr<GraphNode> nextTarget = nullptr;
public:
	PacManBaseState(std::shared_ptr<GamePlayObject> object) : BaseState(object) {}
	virtual void update(double deltaTime);
	virtual void check();

private:
	void calcNextTaget();
};

