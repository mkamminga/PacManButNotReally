#pragma once
#include "BaseState.h"
#include "SparseGraph.h"

class GhostChasingState :
	public BaseState
{
private:
	ShortestRoute lastRoute;
	std::shared_ptr<GraphNode> nextTarget = nullptr;
public:
	GhostChasingState(std::shared_ptr<GamePlayObject> object) : BaseState(object) {}
	virtual void update(double deltaTime);
	virtual void check();
	virtual void accept(BaseVisitor* bv, BaseObject* bo);
};
