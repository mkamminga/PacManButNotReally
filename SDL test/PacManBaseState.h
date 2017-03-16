#pragma once
#include "BaseState.h"
#include "GraphNode.h"

class PacManBaseState :
	public BaseState
{
private:
	std::shared_ptr<GraphNode> lastVisited[2];
public:
	PacManBaseState(std::shared_ptr<GamePlayObject> object) : BaseState(object) {}
	virtual void update(double deltaTime);
	virtual void check();
	virtual void updateAvgCatchTime();
	virtual void accept(BaseVisitor* bv, BaseObject* bo) {}

private:
	void calcNextTaget();
};

