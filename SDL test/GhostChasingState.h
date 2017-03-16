#pragma once
#include "GhostBaseState.h"
#include "SparseGraph.h"

class GhostChasingState :
	public GhostBaseState
{
private:
	ShortestRoute lastRoute;
	std::shared_ptr<GraphNode> targetNode = nullptr;
	std::shared_ptr<GraphNode> nextNode = nullptr;
	std::shared_ptr<GraphNode> lastTarget = nullptr;
public:
	GhostChasingState(std::shared_ptr<GamePlayObject> object, std::shared_ptr<GhostManager> ghostManager, std::shared_ptr<GraphNode> lastTarget) : lastTarget(lastTarget), GhostBaseState(object, ghostManager) {}
	virtual void update(double deltaTime);
	virtual void check();
	virtual void updateAvgCatchTime();
	virtual void accept(BaseVisitor* bv, BaseObject* bo);
};

