#include "GhostWanderingState.h"
#include "GhostChasingState.h"

void GhostWanderingState::check()
{
	auto currentItems = object->getNode()->getItems();

	if (currentItems.size() > 0)
	{
		//object->useItems();
		//TODO: update state 
		object->setState(move(std::make_unique<GhostChasingState>(object)));
	}
}

void GhostWanderingState::accept(BaseVisitor * bv, BaseObject * bo)
{
	bv->visit(this, bo);
}
