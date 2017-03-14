#include "GhostObject.h"
#include "GhostWanderingState.h"

void GhostObject::accept(BaseVisitor * bs)
{
	currentState->accept(bs, this);
}

void GhostObject::update(double deltaTime)
{
	currentState->check();
	currentState->update(deltaTime);
}
