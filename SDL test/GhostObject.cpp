#include "GhostObject.h"
#include "GhostWanderingState.h"

void GhostObject::accept(BaseVisitor * bs)
{
	currentState->accept(bs, this);
}

void GhostObject::update(double deltaTime)
{

	if (!currentState)
	{
		setState(std::make_shared<GhostWanderingState>(shared_from_this(), getWanderingTime()));
	}

	currentState->check();

	currentState->update(deltaTime);
}
