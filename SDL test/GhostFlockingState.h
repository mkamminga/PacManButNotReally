#pragma once
#include "GhostBaseState.h"
class GhostFlockingState :
	public GhostBaseState
{
public:
	GhostFlockingState(std::shared_ptr<GamePlayObject> object, std::shared_ptr<GhostManager> ghostManager) : GhostBaseState(object, ghostManager) {}
	virtual void update(double deltaTime);
	virtual void check();
	virtual void accept(BaseVisitor* bv, BaseObject* bo);
	virtual void updateAvgCatchTime() {}
};

