#pragma once
#include "PacManBaseState.h"

class GhostWanderingState :
	public PacManBaseState
{
public:
	GhostWanderingState(std::shared_ptr<GamePlayObject> object) : PacManBaseState(object) {}
	virtual void check();
	virtual void accept(BaseVisitor* bv, BaseObject* bo);
};

