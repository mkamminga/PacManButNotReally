#include "GhostWanderingState.h"
#include "GhostChasingState.h"
#include <iostream>


void GhostWanderingState::check()
{
	if (!registerd)
	{
		auto shared = shared_from_this();
		mainTimer.subscribe(shared);
		registerd = true;
	}

	auto currentItems = object->getNode()->getItems();

	if (wanderingTime == 0)
	{
		mainTimer.unsubscribe(shared_from_this());

		object->setState(std::make_shared<GhostChasingState>(object));
	}
}

void GhostWanderingState::accept(BaseVisitor * bv, BaseObject * bo)
{
	bv->visit(this, bo);
}

void GhostWanderingState::tick()
{
	if (wanderingTime > 0)
	{
		wanderingTime--;
	}
}
