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
		currentState = std::make_unique<GhostWanderingState>(this->shared_from_this());
	}

	currentState->check();

	currentState->update(deltaTime);
}
