#pragma once
#include "GhostBaseState.h"
#include "SparseGraph.h"

class GhostChasingPillState :
	public GhostBaseState
{
private:
	ShortestRoute lastRoute;
	std::shared_ptr<GraphNode> target = nullptr;
	std::shared_ptr<GraphNode> nextNode = nullptr;
	std::shared_ptr<GraphNode> oldTarget = nullptr;
public:
	GhostChasingPillState(std::shared_ptr<GamePlayObject> object, std::shared_ptr<GhostManager> ghostManager, std::shared_ptr<GraphNode> oldTarget) : oldTarget(oldTarget), GhostBaseState(object, ghostManager) {}
	virtual void update(double deltaTime);
	virtual void check();
	virtual void updateAvgCatchTime();
	virtual void accept(BaseVisitor* bv, BaseObject* bo);
};

