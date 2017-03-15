#include "GhostFlockingState.h"

void GhostFlockingState::update(double deltaTime)
{
}

void GhostFlockingState::check()
{
}

void GhostFlockingState::accept(BaseVisitor * bv, BaseObject * bo)
{
	bv->visit(this, bo);
}
