#pragma once
#include "GhostBaseState.h"
#include "SparseGraph.h"

class GhostChasingState :
	public GhostBaseState
{
private:
	ShortestRoute lastRoute;
	std::shared_ptr<GraphNode> nextTarget = nullptr;
	std::shared_ptr<Route> nextRoute = nullptr;
public:
	GhostChasingState(std::shared_ptr<GamePlayObject> object, std::shared_ptr<GhostManager> ghostManager) : GhostBaseState(object, ghostManager) {}
	virtual void update(double deltaTime);
	virtual void check();
	virtual void accept(BaseVisitor* bv, BaseObject* bo);
};

