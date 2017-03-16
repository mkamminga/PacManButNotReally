#include "GhostWanderingState.h"
#include "GhostChasingState.h"
#include "GhostChasingPillState.h"
#include <iostream>
#include "Random.h"
#include "GhostManager.h"

void GhostWanderingState::update(double deltaTime)
{
	if (wanderingTime == 0)
	{
		mainTimer.unsubscribe(shared_from_this());
		object->setState( ghostManager->getNextRandomState(object, nullptr) );
	}
}

void GhostWanderingState::check()
{
	if (!registerd)
	{
		auto shared = shared_from_this();
		mainTimer.subscribe(shared);
		registerd = true;
	}
}

void GhostWanderingState::accept(BaseVisitor * bv, BaseObject * bo)
{
	bv->visit(this, bo);
}

void GhostWanderingState::updateAvgCatchTime()
{
	ghostManager->updateAvgCatchTime(this);
}

void GhostWanderingState::tick()
{
	if (wanderingTime > 0)
	{
		wanderingTime--;
	}
}